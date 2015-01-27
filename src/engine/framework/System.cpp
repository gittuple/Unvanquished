/*
===========================================================================
Daemon BSD Source Code
Copyright (c) 2013-2014, Daemon Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Daemon developers nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DAEMON DEVELOPERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===========================================================================
*/

#include "../qcommon/q_shared.h"
#include "../qcommon/qcommon.h"
#include "ConsoleHistory.h"
#include "CommandSystem.h"
#include "System.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/file.h>
#endif
#if defined(_WIN32) || defined(BUILD_CLIENT)
#include <SDL.h>
#endif

namespace Sys {

// Allow a client and a server to share the same homepath
#ifdef BUILD_SERVER
#define SERVER_SUFFIX "-server"
#else
#define SERVER_SUFFIX ""
#endif

#ifdef _WIN32
static HANDLE singletonSocket;
#else
static int singletonSocket;
static FS::File lockFile;
static bool haveSingletonLock = false;
#endif
static std::string singletonSocketPath;

// Get the path of a singleton socket
static std::string GetSingletonSocketPath()
{
	// Use the hash of the homepath to identify instances sharing a homepath
	const std::string& homePath = FS::GetHomePath();
	char homePathHash[33] = "";
	Com_MD5Buffer(homePath.data(), homePath.size(), homePathHash, sizeof(homePathHash));
#ifdef _WIN32
	return std::string("\\\\.\\pipe\\" PRODUCT_NAME SERVER_SUFFIX "-") + homePathHash;
#else
	// We use a temporary directory rather that using the homepath because
	// socket paths are limited to about 100 characters. This also avoids issues
	// when the homepath is on a network filesystem.
	return std::string("/tmp/." PRODUCT_NAME_LOWER SERVER_SUFFIX "-") + homePathHash + "/socket";
#endif
}

// Create a socket to listen for commands from other instances
static void CreateSingletonSocket()
{
#ifdef _WIN32
	singletonSocket = CreateNamedPipeA(singletonSocketPath.c_str(), PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 4096, 4096, 1000, NULL);
	if (singletonSocket == INVALID_HANDLE_VALUE)
		Sys::Error("Could not create singleton socket: %s", Sys::Win32StrError(GetLastError()));
#else
	// Grab a lock to avoid race conditions. This lock is automatically released when
	// the process quits, but it may remain if the homepath is on a network filesystem.
	// We restrict the permissions to owner-only to prevent other users from grabbing
	// an exclusive lock (which only requires read access).
	try {
		mode_t oldMask = umask(0077);
		lockFile = FS::HomePath::OpenWrite("lock" SERVER_SUFFIX);
		umask(oldMask);
		if (flock(fileno(lockFile.GetHandle()), LOCK_EX | LOCK_NB) == -1)
			throw std::system_error(errno, std::generic_category());
	} catch (std::system_error& err) {
		Sys::Error("Could not acquire singleton lock: %s\n"
		           "If you are sure no other instance is running, delete %s", err.what(), FS::Path::Build(FS::GetHomePath(), "lock" SERVER_SUFFIX));
	}
	haveSingletonLock = true;

	// Delete any stale sockets
	std::string dirName = FS::Path::DirName(singletonSocketPath);
	unlink(singletonSocketPath.c_str());
	rmdir(dirName.c_str());

	singletonSocket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (singletonSocket == -1)
		Sys::Error("Could not create singleton socket: %s", strerror(errno));

	// Set socket permissions to only be accessible to the current user
	fchmod(singletonSocket, 0600);
	mkdir(dirName.c_str(), 0700);

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	Q_strncpyz(addr.sun_path, singletonSocketPath.c_str(), sizeof(addr.sun_path));
	if (bind(singletonSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1)
		Sys::Error("Could not bind singleton socket: %s", strerror(errno));

	if (listen(singletonSocket, SOMAXCONN) == -1)
		Sys::Error("Could not listen on singleton socket: %s", strerror(errno));
#endif
}

// Try to connect to an existing socket to send our commands to an existing instance
static bool ConnectSingletonSocket()
{
#ifdef _WIN32
	while (true) {
		singletonSocket = CreateFileA(singletonSocketPath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (singletonSocket != INVALID_HANDLE_VALUE)
			break;
		if (GetLastError() != ERROR_PIPE_BUSY) {
			if (GetLastError() != ERROR_FILE_NOT_FOUND)
				Log::Warn("Could not connect to existing instance: %s", Sys::Win32StrError(GetLastError()));
			return false;
		}
		WaitNamedPipeA(singletonSocketPath.c_str(), NMPWAIT_WAIT_FOREVER);
	}

	return true;
#else
	singletonSocket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (singletonSocket == -1)
		Sys::Error("Could not create socket: %s", strerror(errno));

	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	Q_strncpyz(addr.sun_path, singletonSocketPath.c_str(), sizeof(addr.sun_path));
	if (connect(singletonSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) == -1) {
		if (errno != ENOENT)
			Log::Warn("Could not connect to existing instance: %s", strerror(errno));
		close(singletonSocket);
		return false;
	}

	return true;
#endif
}

// Send commands to the existing instance
static void WriteSingletonSocket(Str::StringRef commands)
{
#ifdef _WIN32
	DWORD result = 0;
	if (!WriteFile(singletonSocket, commands.data(), commands.size(), &result, NULL))
		Log::Warn("Could not send commands through socket: %s", Sys::Win32StrError(GetLastError()));
	else if (result != commands.size())
		Log::Warn("Could not send commands through socket: Short write");
#else
	ssize_t result = write(singletonSocket, commands.data(), commands.size());
	if (result == -1 || static_cast<size_t>(result) != commands.size())
		Log::Warn("Could not send commands through socket: %s", result == -1 ? strerror(errno) : "Short write");
#endif
}

// Handle any commands sent by other instances
#ifdef _WIN32
static void ReadSingletonSocketCommands()
{
	std::string commands;
	char buffer[4096];
	while (true) {
		DWORD result = 0;
		if (!ReadFile(singletonSocket, buffer, sizeof(buffer), &result, NULL)) {
			if (GetLastError() != ERROR_NO_DATA && GetLastError() != ERROR_BROKEN_PIPE) {
				Log::Warn("Singleton socket ReadFile() failed: %s", Sys::Win32StrError(GetLastError()));
				return;
			} else
				break;
		}
		if (result == 0)
			break;
		commands.append(buffer, result);
	}

	Cmd::BufferCommandText(commands);
}
#else
static void ReadSingletonSocketCommands(int sock)
{
	std::string commands;
	char buffer[4096];
	while (true) {
		ssize_t result = read(sock, buffer, sizeof(buffer));
		if (result == -1) {
			Log::Warn("Singleton socket read() failed: %s", strerror(errno));
			return;
		}
		if (result == 0)
			break;
		commands.append(buffer, result);
	}

	Cmd::BufferCommandText(commands);
}
#endif
void ReadSingletonSocket()
{
#ifdef _WIN32
	while (true) {
		if (!ConnectNamedPipe(singletonSocket, NULL)) {
			Log::Warn("Singleton socket ConnectNamedPipe() failed: %s", Sys::Win32StrError(GetLastError()));

			// Stop handling incoming commands if an error occured
			CloseHandle(singletonSocket);
			return;
		}

		ReadSingletonSocketCommands();
		DisconnectNamedPipe(singletonSocket);
	}
#else
	while (true) {
		int sock = accept(singletonSocket, NULL, NULL);
		if (sock == -1) {
			Log::Warn("Singleton socket accept() failed: %s", strerror(errno));

			// Stop handling incoming commands if an error occured
			close(singletonSocket);
			return;
		}

		ReadSingletonSocketCommands(sock);
		close(sock);
	}
#endif
}

static void CloseSingletonSocket()
{
#ifdef _WIN32
	CloseHandle(singletonSocket);
#else
	if (!haveSingletonLock)
		return;
	std::string dirName = FS::Path::DirName(singletonSocketPath);
	unlink(singletonSocketPath.c_str());
	rmdir(dirName.c_str());
	try {
		FS::HomePath::DeleteFile("lock" SERVER_SUFFIX);
	} catch (std::system_error&) {}
#endif
}

// Common code for fatal and non-fatal exit
// TODO: Handle shutdown requests coming from multiple threads
// TODO: Dump log files & other stuff
static void Shutdown(bool error, Str::StringRef message)
{
	// Stop accepting commands from other instances
	CloseSingletonSocket();

	// Catch any errors in one stage of shutdown and just skip to the next one
	try {
		CL_Shutdown();
	} catch (Sys::DropErr&) {}
	try {
		SV_Shutdown(error ? va("Server fatal crashed: %s\n", message.c_str()) : va("%s\n", message.c_str()));
	} catch (Sys::DropErr&) {}
	try {
		Com_Shutdown();
	} catch (Sys::DropErr&) {}

	// Always run CON_Shutdown, because it restores the terminal to a usable state.
	CON_Shutdown();

	// Always run SDL_Quit, because it restores system resolution and gamma.
#if defined(_WIN32) || defined(BUILD_CLIENT)
	SDL_Quit();
#endif
}

void Quit(Str::StringRef message)
{
	Shutdown(false, message);

	exit(0);
}

void Error(Str::StringRef message)
{
	// Crash immediately in case of a recursive error
	static std::atomic_flag errorEntered;
	if (errorEntered.test_and_set())
		_exit(-1);

	Log::Error(message);

#if defined(_WIN32) || defined(BUILD_CLIENT)
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, PRODUCT_NAME, message.c_str(), nullptr);
#endif

	Shutdown(true, message);

	exit(1);
}

// Translate non-fatal signals into a quit command
#ifndef _WIN32
static void SignalThread()
{
	// Wait for the signals we are interested in
	sigset_t sigset;
	sigemptyset(&sigset);
	for (int sig: {SIGTERM, SIGINT, SIGQUIT, SIGPIPE, SIGHUP})
		sigaddset(&sigset, sig);
	int sig;
	sigwait(&sigset, &sig);

	// Queue a quit command to be executed next frame
	Cmd::BufferCommandText("quit");

	// Sleep a bit, and wait for a signal again. If we still haven't shut down
	// by then, trigger an error.
	Sys::SleepFor(std::chrono::seconds(2));
	sigwait(&sigset, &sig);
	Sys::Error("Forcing shutdown from signal: %s", strsignal(sig));
}
static void StartSignalThread()
{
	// Block all signals we are interested in. This will cause the signals to be
	// blocked in all threads since they inherit the signal mask.
	sigset_t sigset;
	sigemptyset(&sigset);
	for (int sig: {SIGTERM, SIGINT, SIGQUIT, SIGPIPE, SIGHUP})
		sigaddset(&sigset, sig);
	pthread_sigmask(SIG_BLOCK, &sigset, nullptr);

	// Start the signal thread
	try {
		std::thread(SignalThread).detach();
	} catch (std::system_error& err) {
		Sys::Error("Could not create signal handling thread: %s", err.what());
	}
}
#endif

// Command line arguments
struct cmdlineArgs_t {
	// The Windows client defaults to curses off because of performance issues
	cmdlineArgs_t()
		: homePath(FS::DefaultHomePath()), libPath(FS::DefaultBasePath()), reset_config(false), use_basepath(true),
#if defined(_WIN32) && defined(BUILD_CLIENT)
	use_curses(false) {}
#else
	use_curses(true) {}
#endif

	std::string homePath;
	std::string libPath;
	std::vector<std::string> paths;

	bool reset_config;
	bool use_basepath;
	bool use_curses;

	std::unordered_map<std::string, std::string> cvars;
	std::string commands;
};

// Parse the command line arguments
#ifdef BUILD_SERVER
#define HELP_URL ""
#else
#define HELP_URL " [" URI_SCHEME "ADDRESS[:PORT]]"
#endif
static void ParseCmdline(int argc, char** argv, cmdlineArgs_t& cmdlineArgs)
{
#ifdef __APPLE__
	// Ignore the -psn parameter added by OSX
	if (!strncmp(argv[argc - 1], "-psn", 4))
		argc--;
#endif

	bool foundCommands = false;
	for (int i = 1; i < argc; i++) {
		// A + indicate the start of a command that should be run on startup
		if (argv[i][0] == '+') {
			foundCommands = true;
			if (!cmdlineArgs.commands.empty())
				cmdlineArgs.commands.push_back('\n');
			cmdlineArgs.commands.append(argv[i] + 1);
			continue;
		}

		// Anything after a + is a parameter for that command
		if (foundCommands) {
			cmdlineArgs.commands.push_back(' ');
			cmdlineArgs.commands.append(Cmd::Escape(argv[i]));
			continue;
		}

#ifndef BUILD_SERVER
		// If a URI is given, transform it into a /connect command. This only
		// applies if no +commands have been given. Any arguments after the URI
		// are discarded.
		if (Str::IsIPrefix(URI_SCHEME, argv[i])) {
			cmdlineArgs.commands = "connect " + Cmd::Escape(argv[i]);
			if (i != argc - 1)
				Log::Warn("Ignoring extraneous arguments after URI");
			return;
		}
#endif

		if (!strcmp(argv[i], "--help")) {
			fprintf(stderr, PRODUCT_NAME " " PRODUCT_VERSION "\n"
			                "Usage: %s [-OPTION]..." HELP_URL " [+COMMAND]...\n",
			                argv[0]);
			exit(0);
		} else if (!strcmp(argv[i], "--version")) {
			fprintf(stderr, PRODUCT_NAME " " PRODUCT_VERSION "\n");
			exit(0);
		} else if (!strcmp(argv[i], "-set")) {
			if (i >= argc - 2) {
				Log::Warn("Missing argument for -set");
				continue;
			}
			cmdlineArgs.cvars[argv[i + 1]] = argv[i + 2];
			i += 2;
		} else if (!strcmp(argv[i], "-nobasepath")) {
			cmdlineArgs.use_basepath = false;
		} else if (!strcmp(argv[i], "-path")) {
			if (i == argc - 1) {
				Log::Warn("Missing argument for -path");
				continue;
			}
			cmdlineArgs.paths.push_back(argv[i + 1]);
			i++;
		} else if (!strcmp(argv[i], "-libpath")) {
			if (i == argc - 1) {
				Log::Warn("Missing argument for -libpath");
				continue;
			}
			cmdlineArgs.libPath = argv[i + 1];
			i++;
		} else if (!strcmp(argv[i], "-homepath")) {
			if (i == argc - 1) {
				Log::Warn("Missing argument for -homepath");
				continue;
			}
			cmdlineArgs.homePath = argv[i + 1];
			i++;
		} else if (!strcmp(argv[i], "-resetconfig")) {
			cmdlineArgs.reset_config = true;
		} else if (!strcmp(argv[i], "-curses")) {
			cmdlineArgs.use_curses = true;
		} else if (!strcmp(argv[i], "-nocurses")) {
			cmdlineArgs.use_curses = false;
		} else {
			Log::Warn("Ignoring unrecognized parameter \"%s\"", argv[i]);
			continue;
		}
	}
}

// Apply a -set argument early, before the configuration files are loaded
static void EarlyCvar(Str::StringRef name, cmdlineArgs_t& cmdlineArgs)
{
	auto it = cmdlineArgs.cvars.find(name);
	if (it != cmdlineArgs.cvars.end())
		Cvar::SetValue(it->first, it->second);
}

// Initialize the engine
static void Init(int argc, char** argv)
{
	cmdlineArgs_t cmdlineArgs;

	// Print a banner and a copy of the command-line arguments
	Log::Notice(Q3_VERSION " " PLATFORM_STRING " " ARCH_STRING " " __DATE__);
	std::string argsString = "cmdline:";
	for (int i = 1; i < argc; i++) {
		argsString.push_back(' ');
		argsString.append(argv[i]);
	}
	Log::Notice(argsString);

	Sys::SetupCrashHandler();
	Sys::ParseCmdline(argc, argv, cmdlineArgs);

	// Platform-specific initialization
#ifdef _WIN32
	// Don't let SDL set the timer resolution. We do that manually in Sys::Sleep.
	SDL_SetHint(SDL_HINT_TIMER_RESOLUTION, "0");

	// Mark the process as DPI-aware on Vista and above, ignore any errors
	std::string errorString;
	Sys::DynamicLib user32 = Sys::DynamicLib::Open("user32.dll", errorString);
	if (user32) {
		auto pSetProcessDPIAware = user32.LoadSym<BOOL WINAPI()>("SetProcessDPIAware", errorString);
		if (pSetProcessDPIAware)
			pSetProcessDPIAware();
	}
#else
	// Translate non-fatal signals to a quit command
	Sys::StartSignalThread();

	// Force a UTF-8 locale for LC_CTYPE so that terminals can output unicode
	// characters. We keep all other locale facets as "C".
	if (!setlocale(LC_CTYPE, "C.UTF-8") || !setlocale(LC_CTYPE, "UTF-8") || !setlocale(LC_CTYPE, "en_US.UTF-8")) {
		// Try using the user's locale with UTF-8
		std::string locale = setlocale(LC_CTYPE, "");
		if (!Str::IsSuffix(".UTF-8", locale)) {
			size_t dot = locale.rfind('.');
			if (dot != std::string::npos)
				locale.replace(dot, locale.size() - dot, ".UTF-8");
			if (!setlocale(LC_CTYPE, locale.c_str())) {
				setlocale(LC_CTYPE, "C");
				Log::Warn("Could not set locale to UTF-8, unicode characters may not display correctly");
			}
		}
	}

	// Enable S3TC on Mesa even if libtxc-dxtn is not available
	putenv("force_s3tc_enable=true");
#endif

	// Initialize the console
	if (cmdlineArgs.use_curses)
		CON_Init();
	else
		CON_Init_TTY();

	// Initialize the filesystem
	if (cmdlineArgs.use_basepath)
		cmdlineArgs.paths.insert(cmdlineArgs.paths.begin(), FS::DefaultBasePath());
	FS::Initialize(cmdlineArgs.homePath, cmdlineArgs.libPath, cmdlineArgs.paths);

	// Look for an existing instance of the engine running on the same homepath.
	// If there is one, forward any +commands to it and exit.
	singletonSocketPath = GetSingletonSocketPath();
	if (ConnectSingletonSocket()) {
		Log::Notice("Existing instance found");
		if (!cmdlineArgs.commands.empty()) {
			Log::Notice("Forwarding commands to existing instance");
			WriteSingletonSocket(cmdlineArgs.commands);
		} else
			Log::Notice("No commands given, exiting...");
#ifdef _WIN32
		CloseHandle(singletonSocket);
#else
		close(singletonSocket);
#endif
		exit(0);
	}

	// Create the singleton socket and a thread to watch it
	CreateSingletonSocket();
	try {
		std::thread(ReadSingletonSocket).detach();
	} catch (std::system_error& err) {
		Sys::Error("Could not create singleton socket thread: %s", err.what());
	}

	// Load the base paks
	// TODO: cvar names and FS_* stuff needs to be properly integrated
	EarlyCvar("fs_basepak", cmdlineArgs);
	EarlyCvar("fs_extrapaks", cmdlineArgs);
	FS_LoadBasePak();

	// Load configuration files
	CL_InitKeyCommands(); // for binds
#ifndef BUILD_SERVER
	Cmd::BufferCommandText("preset default.cfg");
#endif
	if (!cmdlineArgs.reset_config) {
#ifdef BUILD_SERVER
		Cmd::BufferCommandText("exec -f " SERVERCONFIG_NAME);
#else
		Cmd::BufferCommandText("exec -f " CONFIG_NAME);
		Cmd::BufferCommandText("exec -f " KEYBINDINGS_NAME);
		Cmd::BufferCommandText("exec -f " AUTOEXEC_NAME);
#endif
	}
	Cmd::ExecuteCommandBuffer();

	// Override any cvars set in configuration files with those on the command-line
	for (auto& cvar: cmdlineArgs.cvars)
		Cvar::SetValue(cvar.first, cvar.second);

	// Load the console history
	Console::LoadHistory();

	// Legacy initialization code, needs to be replaced
	// TODO: eventually move all of Com_Init into here
	Com_Init("");

	// Buffer the commands that were specified on the command line so they are
	// executed in the first frame.
	Cmd::BufferCommandText(cmdlineArgs.commands);
}

} // namespace Sys

// GCC expects a 16-byte aligned stack but Windows only guarantees 4-byte alignment.
// The MinGW startup code should be handling this but for some reason it isn't.
#if defined(_WIN32) && defined(__GNUC__) && defined(__i386__)
#define ALIGN_STACK __attribute__((force_align_arg_pointer))
#else
#define ALIGN_STACK
#endif

// Program entry point. On Windows, main is #defined to SDL_main which is
// invoked by SDLmain.
ALIGN_STACK int main(int argc, char** argv)
{
	// Initialize the engine. Any errors here are fatal.
	try {
		Sys::Init(argc, argv);
	} catch (Sys::DropErr& err) {
		Sys::Error("Error during initialization: %s", err.what());
	} catch (std::exception& err) {
		Sys::Error("Unhandled exception (%s): %s", typeid(err).name(), err.what());
	} catch (...) {
		Sys::Error("Unhandled exception of unknown type");
	}

	// Run the engine frame in a loop. First try to handle an error by returning
	// to the menu, but make the error fatal if the shutdown code fails.
	try {
		while (true) {
			try {
				Com_Frame();
			} catch (Sys::DropErr& err) {
				Log::Error(err.what());
				FS::PakPath::ClearPaks();
				FS_LoadBasePak();
				SV_Shutdown(va("********************\nServer crashed: %s\n********************\n", err.what()));
				CL_Disconnect(qtrue);
				CL_FlushMemory();
			}
		}
	} catch (Sys::DropErr& err) {
		Sys::Error("Error during error handling: %s", err.what());
	} catch (std::exception& err) {
		Sys::Error("Unhandled exception (%s): %s", typeid(err).name(), err.what());
	} catch (...) {
		Sys::Error("Unhandled exception of unknown type");
	}
}