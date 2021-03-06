# Create libRocket.

set(Core_HDR_FILES
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorFirstOfType.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledBoxInstancer.h
    ${ROCKET_DIR}/Source/Core/ElementStyle.h
    ${ROCKET_DIR}/Source/Core/ElementStyleCache.h
    ${ROCKET_DIR}/Source/Core/ContextInstancerDefault.h
    ${ROCKET_DIR}/Source/Core/PropertyParserKeyword.h
    ${ROCKET_DIR}/Source/Core/ElementDefinition.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorOnlyChild.h
    ${ROCKET_DIR}/Source/Core/DecoratorNoneInstancer.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledHorizontal.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledImageInstancer.h
    ${ROCKET_DIR}/Source/Core/PluginRegistry.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorEmpty.h
    ${ROCKET_DIR}/Source/Core/StyleSheetParser.h
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerTemplate.h
    ${ROCKET_DIR}/Source/Core/PropertyShorthandDefinition.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthOfType.h
    ${ROCKET_DIR}/Source/Core/ElementTextDefault.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelector.h
    ${ROCKET_DIR}/Source/Core/FontEffectShadowInstancer.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorLastOfType.h
    ${ROCKET_DIR}/Source/Core/TextureLayoutRow.h
    ${ROCKET_DIR}/Source/Core/ElementBackground.h
    ${ROCKET_DIR}/Source/Core/PropertyParserString.h
    ${ROCKET_DIR}/Source/Core/TextureResource.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNode.h
    ${ROCKET_DIR}/Source/Core/Clock.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledInstancer.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledImage.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledVerticalInstancer.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorLastChild.h
    ${ROCKET_DIR}/Source/Core/ElementHandle.h
    ${ROCKET_DIR}/Source/Core/EventDispatcher.h
    ${ROCKET_DIR}/Source/Core/Pool.h
    ${ROCKET_DIR}/Source/Core/TemplateCache.h
    ${ROCKET_DIR}/Source/Core/Template.h
    ${ROCKET_DIR}/Source/Core/EventIterators.h
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerBody.h
    ${ROCKET_DIR}/Source/Core/LayoutBlockBox.h
    ${ROCKET_DIR}/Source/Core/WidgetSlider.h
    ${ROCKET_DIR}/Source/Core/LayoutInlineBoxText.h
    ${ROCKET_DIR}/Source/Core/FontFaceLayer.h
    ${ROCKET_DIR}/Source/Core/ElementImage.h
    ${ROCKET_DIR}/Source/Core/FontFamily.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiled.h
    ${ROCKET_DIR}/Source/Core/PropertyParserColour.h
    ${ROCKET_DIR}/Source/Core/XMLParseTools.h
    ${ROCKET_DIR}/Source/Core/WidgetSliderScroll.h
    ${ROCKET_DIR}/Source/Core/LayoutBlockBoxSpace.h
    ${ROCKET_DIR}/Source/Core/DocumentHeader.h
    ${ROCKET_DIR}/Source/Core/precompiled.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthLastChild.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorFirstChild.h
    ${ROCKET_DIR}/Source/Core/LayoutLineBox.h
    ${ROCKET_DIR}/Source/Core/DebugFont.h
    ${ROCKET_DIR}/Source/Core/FontEffectNone.h
    ${ROCKET_DIR}/Source/Core/FontEffectShadow.h
    ${ROCKET_DIR}/Source/Core/TextureDatabase.h
    ${ROCKET_DIR}/Source/Core/PropertyParserNumber.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledVertical.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthChild.h
    ${ROCKET_DIR}/Source/Core/TextureLayoutRectangle.h
    ${ROCKET_DIR}/Source/Core/LayoutInlineBox.h
    ${ROCKET_DIR}/Source/Core/GeometryDatabase.h
    ${ROCKET_DIR}/Source/Core/FontEffectOutlineInstancer.h
    ${ROCKET_DIR}/Source/Core/TextureLayoutTexture.h
    ${ROCKET_DIR}/Source/Core/FontFace.h
    ${ROCKET_DIR}/Source/Core/TextureLayout.h
    ${ROCKET_DIR}/Source/Core/EventInstancerDefault.h
    ${ROCKET_DIR}/Source/Core/ElementBorder.h
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerHead.h
    ${ROCKET_DIR}/Source/Core/ElementDecoration.h
    ${ROCKET_DIR}/Source/Core/StreamFile.h
    ${ROCKET_DIR}/Source/Core/LayoutEngine.h
    ${ROCKET_DIR}/Source/Core/FontEffectOutline.h
    ${ROCKET_DIR}/Source/Core/StyleSheetFactory.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthLastOfType.h
    ${ROCKET_DIR}/Source/Core/FileInterfaceDefault.h
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerDefault.h
    ${ROCKET_DIR}/Source/Core/DecoratorNone.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledHorizontalInstancer.h
    ${ROCKET_DIR}/Source/Core/StringCache.h
    ${ROCKET_DIR}/Source/Core/FontEffectNoneInstancer.h
    ${ROCKET_DIR}/Source/Core/DecoratorTiledBox.h
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorOnlyOfType.h
)

set(Core_PUB_HDR_FILES
    ${ROCKET_DIR}/Include/Rocket/Core/FontEffect.h
    ${ROCKET_DIR}/Include/Rocket/Core/TypeConverter.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementScroll.h
    ${ROCKET_DIR}/Include/Rocket/Core/SystemInterface.h
    ${ROCKET_DIR}/Include/Rocket/Core/Colour.h
    ${ROCKET_DIR}/Include/Rocket/Core/Box.h
    ${ROCKET_DIR}/Include/Rocket/Core/ConvolutionFilter.h
    ${ROCKET_DIR}/Include/Rocket/Core/EventListenerInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementInstancerGeneric.h
    ${ROCKET_DIR}/Include/Rocket/Core/FileInterface.h
    ${ROCKET_DIR}/Include/Rocket/Core/MathTypes.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/PropertySpecification.h
    ${ROCKET_DIR}/Include/Rocket/Core/Property.h
    ${ROCKET_DIR}/Include/Rocket/Core/Plugin.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementReference.h
    ${ROCKET_DIR}/Include/Rocket/Core/StreamMemory.h
    ${ROCKET_DIR}/Include/Rocket/Core/WString.h
    ${ROCKET_DIR}/Include/Rocket/Core/EventListener.h
    ${ROCKET_DIR}/Include/Rocket/Core/PropertyDefinition.h
    ${ROCKET_DIR}/Include/Rocket/Core/Decorator.h
    ${ROCKET_DIR}/Include/Rocket/Core/Texture.h
    ${ROCKET_DIR}/Include/Rocket/Core/PropertyDictionary.h
    ${ROCKET_DIR}/Include/Rocket/Core/StyleSheet.h
    ${ROCKET_DIR}/Include/Rocket/Core/FontGlyph.h
    ${ROCKET_DIR}/Include/Rocket/Core/ReferenceCountable.h
    ${ROCKET_DIR}/Include/Rocket/Core/StringUtilities.h
    ${ROCKET_DIR}/Include/Rocket/Core/Vertex.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementUtilities.h
    ${ROCKET_DIR}/Include/Rocket/Core/Factory.h
    ${ROCKET_DIR}/Include/Rocket/Core/Stream.h
    ${ROCKET_DIR}/Include/Rocket/Core/GeometryUtilities.h
    ${ROCKET_DIR}/Include/Rocket/Core/Vector2.h
    ${ROCKET_DIR}/Include/Rocket/Core/StyleSheetSpecification.h
    ${ROCKET_DIR}/Include/Rocket/Core/RenderInterface.h
    ${ROCKET_DIR}/Include/Rocket/Core/StyleSheetKeywords.h
    ${ROCKET_DIR}/Include/Rocket/Core/Core.h
    ${ROCKET_DIR}/Include/Rocket/Core/FontDatabase.h
    ${ROCKET_DIR}/Include/Rocket/Core/Header.h
    ${ROCKET_DIR}/Include/Rocket/Core/Dictionary.h
    ${ROCKET_DIR}/Include/Rocket/Core/Types.h
    ${ROCKET_DIR}/Include/Rocket/Core/XMLParser.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementDocument.h
    ${ROCKET_DIR}/Include/Rocket/Core/BaseXMLParser.h
    ${ROCKET_DIR}/Include/Rocket/Core/Debug.h
    ${ROCKET_DIR}/Include/Rocket/Core/URL.h
    ${ROCKET_DIR}/Include/Rocket/Core/Input.h
    ${ROCKET_DIR}/Include/Rocket/Core/Event.h
    ${ROCKET_DIR}/Include/Rocket/Core/Geometry.h
    ${ROCKET_DIR}/Include/Rocket/Core/Font.h
    ${ROCKET_DIR}/Include/Rocket/Core/ElementText.h
    ${ROCKET_DIR}/Include/Rocket/Core/String.h
    ${ROCKET_DIR}/Include/Rocket/Core/Element.h
    ${ROCKET_DIR}/Include/Rocket/Core/ScriptInterface.h
    ${ROCKET_DIR}/Include/Rocket/Core/StringBase.h
    ${ROCKET_DIR}/Include/Rocket/Core/EventInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/DecoratorInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/Context.h
    ${ROCKET_DIR}/Include/Rocket/Core/FontEffectInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/Variant.h
    ${ROCKET_DIR}/Include/Rocket/Core/Math.h
    ${ROCKET_DIR}/Include/Rocket/Core/Log.h
    ${ROCKET_DIR}/Include/Rocket/Core/Platform.h
    ${ROCKET_DIR}/Include/Rocket/Core/XMLNodeHandler.h
    ${ROCKET_DIR}/Include/Rocket/Core/PropertyParser.h
    ${ROCKET_DIR}/Include/Rocket/Core/ContextInstancer.h
    ${ROCKET_DIR}/Include/Rocket/Core/UnicodeRange.h
    ${ROCKET_DIR}/Include/Rocket/Core/FontFaceHandle.h
    ${ROCKET_DIR}/Include/Rocket/Core.h
)

set(Core_SRC_FILES
    ${ROCKET_DIR}/Source/Core/StreamMemory.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledVertical.cpp
    ${ROCKET_DIR}/Source/Core/EventInstancerDefault.cpp
    ${ROCKET_DIR}/Source/Core/ElementHandle.cpp
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerBody.cpp
    ${ROCKET_DIR}/Source/Core/TextureDatabase.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledBox.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetParser.cpp
    ${ROCKET_DIR}/Source/Core/Core.cpp
    ${ROCKET_DIR}/Source/Core/Template.cpp
    ${ROCKET_DIR}/Source/Core/XMLNodeHandler.cpp
    ${ROCKET_DIR}/Source/Core/String.cpp
    ${ROCKET_DIR}/Source/Core/ReferenceCountable.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorLastOfType.cpp
    ${ROCKET_DIR}/Source/Core/ElementBackground.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledHorizontal.cpp
    ${ROCKET_DIR}/Source/Core/EventDispatcher.cpp
    ${ROCKET_DIR}/Source/Core/EventListenerInstancer.cpp
    ${ROCKET_DIR}/Source/Core/StringCache.cpp
    ${ROCKET_DIR}/Source/Core/ElementUtilities.cpp
    ${ROCKET_DIR}/Source/Core/TemplateCache.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledBoxInstancer.cpp
    ${ROCKET_DIR}/Source/Core/Event.cpp
    ${ROCKET_DIR}/Source/Core/Clock.cpp
    ${ROCKET_DIR}/Source/Core/GeometryDatabase.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorOnlyChild.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectInstancer.cpp
    ${ROCKET_DIR}/Source/Core/ElementDecoration.cpp
    ${ROCKET_DIR}/Source/Core/FontEffect.cpp
    ${ROCKET_DIR}/Source/Core/FileInterfaceDefault.cpp
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerTemplate.cpp
    ${ROCKET_DIR}/Source/Core/ConvolutionFilter.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiled.cpp
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerHead.cpp
    ${ROCKET_DIR}/Source/Core/DocumentHeader.cpp
    ${ROCKET_DIR}/Source/Core/ContextInstancer.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledInstancer.cpp
    ${ROCKET_DIR}/Source/Core/Decorator.cpp
    ${ROCKET_DIR}/Source/Core/BaseXMLParser.cpp
    ${ROCKET_DIR}/Source/Core/Box.cpp
    ${ROCKET_DIR}/Source/Core/PropertyDefinition.cpp
    ${ROCKET_DIR}/Source/Core/Math.cpp
    ${ROCKET_DIR}/Source/Core/ElementText.cpp
    ${ROCKET_DIR}/Source/Core/precompiled.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetSpecification.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectNone.cpp
    ${ROCKET_DIR}/Source/Core/PluginRegistry.cpp
    ${ROCKET_DIR}/Source/Core/ElementInstancer.cpp
    ${ROCKET_DIR}/Source/Core/RenderInterface.cpp
    ${ROCKET_DIR}/Source/Core/ContextInstancerDefault.cpp
    ${ROCKET_DIR}/Source/Core/LayoutInlineBoxText.cpp
    ${ROCKET_DIR}/Source/Core/TextureLayout.cpp
    ${ROCKET_DIR}/Source/Core/PropertyDictionary.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorInstancer.cpp
    ${ROCKET_DIR}/Source/Core/Context.cpp
    ${ROCKET_DIR}/Source/Core/LayoutEngine.cpp
    ${ROCKET_DIR}/Source/Core/WidgetSlider.cpp
    ${ROCKET_DIR}/Source/Core/Property.cpp
    ${ROCKET_DIR}/Source/Core/ElementStyle.cpp
    ${ROCKET_DIR}/Source/Core/ElementStyleCache.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorNoneInstancer.cpp
    ${ROCKET_DIR}/Source/Core/Element.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectOutlineInstancer.cpp
    ${ROCKET_DIR}/Source/Core/FontDatabase.cpp
    ${ROCKET_DIR}/Source/Core/Texture.cpp
    ${ROCKET_DIR}/Source/Core/ElementScroll.cpp
    ${ROCKET_DIR}/Source/Core/FontFaceLayer.cpp
    ${ROCKET_DIR}/Source/Core/UnicodeRange.cpp
    ${ROCKET_DIR}/Source/Core/FileInterface.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthLastChild.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectShadow.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetFactory.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorLastChild.cpp
    ${ROCKET_DIR}/Source/Core/LayoutBlockBoxSpace.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectNoneInstancer.cpp
    ${ROCKET_DIR}/Source/Core/FontFace.cpp
    ${ROCKET_DIR}/Source/Core/Vector2.cpp
    ${ROCKET_DIR}/Source/Core/PropertyParserKeyword.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNode.cpp
    ${ROCKET_DIR}/Source/Core/ElementDocument.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorEmpty.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledImageInstancer.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectOutline.cpp
    ${ROCKET_DIR}/Source/Core/FontFamily.cpp
    ${ROCKET_DIR}/Source/Core/WString.cpp
    ${ROCKET_DIR}/Source/Core/URL.cpp
    ${ROCKET_DIR}/Source/Core/FontEffectShadowInstancer.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledHorizontalInstancer.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorNone.cpp
    ${ROCKET_DIR}/Source/Core/StreamFile.cpp
    ${ROCKET_DIR}/Source/Core/Dictionary.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledImage.cpp
    ${ROCKET_DIR}/Source/Core/EventInstancer.cpp
    ${ROCKET_DIR}/Source/Core/TextureLayoutRow.cpp
    ${ROCKET_DIR}/Source/Core/PropertySpecification.cpp
    ${ROCKET_DIR}/Source/Core/FontFaceHandle.cpp
    ${ROCKET_DIR}/Source/Core/SystemInterface.cpp
    ${ROCKET_DIR}/Source/Core/ElementBorder.cpp
    ${ROCKET_DIR}/Source/Core/Plugin.cpp
    ${ROCKET_DIR}/Source/Core/LayoutLineBox.cpp
    ${ROCKET_DIR}/Source/Core/TextureLayoutRectangle.cpp
    ${ROCKET_DIR}/Source/Core/TextureResource.cpp
    ${ROCKET_DIR}/Source/Core/LayoutBlockBox.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthOfType.cpp
    ${ROCKET_DIR}/Source/Core/ElementImage.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelector.cpp
    ${ROCKET_DIR}/Source/Core/GeometryUtilities.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthLastOfType.cpp
    ${ROCKET_DIR}/Source/Core/WidgetSliderScroll.cpp
    ${ROCKET_DIR}/Source/Core/XMLParseTools.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorFirstOfType.cpp
    ${ROCKET_DIR}/Source/Core/ElementTextDefault.cpp
    ${ROCKET_DIR}/Source/Core/PropertyParserNumber.cpp
    ${ROCKET_DIR}/Source/Core/XMLNodeHandlerDefault.cpp
    ${ROCKET_DIR}/Source/Core/TextureLayoutTexture.cpp
    ${ROCKET_DIR}/Source/Core/Stream.cpp
    ${ROCKET_DIR}/Source/Core/XMLParser.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheet.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorFirstChild.cpp
    ${ROCKET_DIR}/Source/Core/StringUtilities.cpp
    ${ROCKET_DIR}/Source/Core/Log.cpp
    ${ROCKET_DIR}/Source/Core/Variant.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorNthChild.cpp
    ${ROCKET_DIR}/Source/Core/Geometry.cpp
    ${ROCKET_DIR}/Source/Core/DecoratorTiledVerticalInstancer.cpp
    ${ROCKET_DIR}/Source/Core/ElementReference.cpp
    ${ROCKET_DIR}/Source/Core/StyleSheetNodeSelectorOnlyOfType.cpp
    ${ROCKET_DIR}/Source/Core/PropertyParserString.cpp
    ${ROCKET_DIR}/Source/Core/PropertyParserColour.cpp
    ${ROCKET_DIR}/Source/Core/Factory.cpp
    ${ROCKET_DIR}/Source/Core/ElementDefinition.cpp
    ${ROCKET_DIR}/Source/Core/LayoutInlineBox.cpp
)

set(Controls_HDR_FILES
    ${ROCKET_DIR}/Source/Controls/WidgetDropDown.h
    ${ROCKET_DIR}/Source/Controls/InputTypeRange.h
    ${ROCKET_DIR}/Source/Controls/WidgetSliderInput.h
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputSingleLine.h
    ${ROCKET_DIR}/Source/Controls/WidgetTextInput.h
    ${ROCKET_DIR}/Source/Controls/InputTypeButton.h
    ${ROCKET_DIR}/Source/Controls/WidgetSlider.h
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputMultiLine.h
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerTabSet.h
    ${ROCKET_DIR}/Source/Controls/InputTypeCheckbox.h
    ${ROCKET_DIR}/Source/Controls/InputTypeSubmit.h
    ${ROCKET_DIR}/Source/Controls/InputTypeRadio.h
    ${ROCKET_DIR}/Source/Controls/ElementTextSelection.h
    ${ROCKET_DIR}/Source/Controls/InputType.h
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerDataGrid.h
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerTextArea.h
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputSingleLinePassword.h
    ${ROCKET_DIR}/Source/Controls/InputTypeText.h
)

set(Controls_PUB_HDR_FILES
    ${ROCKET_DIR}/Include/Rocket/Controls/DataQuery.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementFormControlDataSelect.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementFormControlTextArea.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementTabSet.h
    ${ROCKET_DIR}/Include/Rocket/Controls/Controls.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementFormControlSelect.h
    ${ROCKET_DIR}/Include/Rocket/Controls/SelectOption.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementFormControlInput.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementFormControl.h
    ${ROCKET_DIR}/Include/Rocket/Controls/Header.h
    ${ROCKET_DIR}/Include/Rocket/Controls/DataSource.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementDataGrid.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementDataGridExpandButton.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementDataGridRow.h
    ${ROCKET_DIR}/Include/Rocket/Controls/Clipboard.h
    ${ROCKET_DIR}/Include/Rocket/Controls/DataFormatter.h
    ${ROCKET_DIR}/Include/Rocket/Controls/DataSourceListener.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementForm.h
    ${ROCKET_DIR}/Include/Rocket/Controls/ElementDataGridCell.h
    ${ROCKET_DIR}/Include/Rocket/Controls.h
)

set(Controls_SRC_FILES
    ${ROCKET_DIR}/Source/Controls/SelectOption.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputSingleLinePassword.cpp
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerDataGrid.cpp
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerTextArea.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetDropDown.cpp
    ${ROCKET_DIR}/Source/Controls/ElementTabSet.cpp
    ${ROCKET_DIR}/Source/Controls/ElementFormControlTextArea.cpp
    ${ROCKET_DIR}/Source/Controls/Clipboard.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputMultiLine.cpp
    ${ROCKET_DIR}/Source/Controls/DataSourceListener.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetSliderInput.cpp
    ${ROCKET_DIR}/Source/Controls/ElementFormControlDataSelect.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeSubmit.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetTextInput.cpp
    ${ROCKET_DIR}/Source/Controls/Controls.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeRadio.cpp
    ${ROCKET_DIR}/Source/Controls/ElementDataGridRow.cpp
    ${ROCKET_DIR}/Source/Controls/ElementFormControlSelect.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetSlider.cpp
    ${ROCKET_DIR}/Source/Controls/ElementDataGridExpandButton.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeText.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeCheckbox.cpp
    ${ROCKET_DIR}/Source/Controls/InputType.cpp
    ${ROCKET_DIR}/Source/Controls/ElementFormControlInput.cpp
    ${ROCKET_DIR}/Source/Controls/ElementDataGrid.cpp
    ${ROCKET_DIR}/Source/Controls/ElementTextSelection.cpp
    ${ROCKET_DIR}/Source/Controls/XMLNodeHandlerTabSet.cpp
    ${ROCKET_DIR}/Source/Controls/DataQuery.cpp
    ${ROCKET_DIR}/Source/Controls/ElementForm.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeButton.cpp
    ${ROCKET_DIR}/Source/Controls/InputTypeRange.cpp
    ${ROCKET_DIR}/Source/Controls/ElementDataGridCell.cpp
    ${ROCKET_DIR}/Source/Controls/ElementFormControl.cpp
    ${ROCKET_DIR}/Source/Controls/WidgetTextInputSingleLine.cpp
    ${ROCKET_DIR}/Source/Controls/DataFormatter.cpp
    ${ROCKET_DIR}/Source/Controls/DataSource.cpp
)

set(Debugger_HDR_FILES
    ${ROCKET_DIR}/Source/Debugger/ElementLog.h
    ${ROCKET_DIR}/Source/Debugger/SystemInterface.h
    ${ROCKET_DIR}/Source/Debugger/InfoSource.h
    ${ROCKET_DIR}/Source/Debugger/Plugin.h
    ${ROCKET_DIR}/Source/Debugger/LogSource.h
    ${ROCKET_DIR}/Source/Debugger/ElementInfo.h
    ${ROCKET_DIR}/Source/Debugger/BeaconSource.h
    ${ROCKET_DIR}/Source/Debugger/Geometry.h
    ${ROCKET_DIR}/Source/Debugger/MenuSource.h
    ${ROCKET_DIR}/Source/Debugger/ElementContextHook.h
    ${ROCKET_DIR}/Source/Debugger/CommonSource.h
    ${ROCKET_DIR}/Source/Debugger/FontSource.h
)

set(Debugger_PUB_HDR_FILES
    ${ROCKET_DIR}/Include/Rocket/Debugger/Header.h
    ${ROCKET_DIR}/Include/Rocket/Debugger/Debugger.h
    ${ROCKET_DIR}/Include/Rocket/Debugger.h
)

set(Debugger_SRC_FILES
    ${ROCKET_DIR}/Source/Debugger/ElementInfo.cpp
    ${ROCKET_DIR}/Source/Debugger/Debugger.cpp
    ${ROCKET_DIR}/Source/Debugger/ElementLog.cpp
    ${ROCKET_DIR}/Source/Debugger/ElementContextHook.cpp
    ${ROCKET_DIR}/Source/Debugger/SystemInterface.cpp
    ${ROCKET_DIR}/Source/Debugger/Plugin.cpp
    ${ROCKET_DIR}/Source/Debugger/Geometry.cpp
)



set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "Release/${GAMELIB_OUTPUT_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "Debug/${GAMELIB_OUTPUT_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "MinSizeRel/${GAMELIB_OUTPUT_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "RelWithDebInfo/${GAMELIB_OUTPUT_DIR}" )

find_package( Freetype REQUIRED )

include_directories( ${ROCKET_DIR}/Include ${FREETYPE_INCLUDE_DIRS} )
add_library( ROCKET_LIB STATIC ${Core_HDR_FILES} ${Core_PUB_HDR_FILES} ${Core_SRC_FILES} ${Controls_HDR_FILES} ${Controls_PUB_HDR_FILES} ${Controls_SRC_FILES}
	${Debugger_HDR_FILES} ${Debugger_PUB_HDR_FILES} ${Debugger_SRC_FILES} )

set_property( TARGET ROCKET_LIB PROPERTY COMPILE_DEFINITIONS STATIC_LIB )
