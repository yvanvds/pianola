/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "test.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
test::test ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (true);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String());

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->addListener (this);
    textButton->setColour (TextButton::buttonColourId, Colour (0xffffbbfb));

    addAndMakeVisible (imageButton = new ImageButton ("new button2"));
    imageButton->addListener (this);

    imageButton->setImages (false, true, true,
                            ImageCache::getFromMemory (BinaryData::led_off_png, BinaryData::led_off_pngSize), 1.000f, Colour (0xffce3838),
                            ImageCache::getFromMemory (BinaryData::led_on_png, BinaryData::led_on_pngSize), 1.000f, Colour (0x00000000),
                            ImageCache::getFromMemory (BinaryData::led_on_png, BinaryData::led_on_pngSize), 1.000f, Colour (0x00000000));
    addAndMakeVisible (toggleButton = new ToggleButton ("new toggle button"));
    toggleButton->addListener (this);

    drawable1 = Drawable::createFromImageData (BinaryData::meccanoid_png, BinaryData::meccanoid_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

test::~test()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditor = nullptr;
    textButton = nullptr;
    imageButton = nullptr;
    toggleButton = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void test::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (124, 148, 100, 100),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void test::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    textEditor->setBounds (56, 24, 150, 24);
    textButton->setBounds (224, 24, 150, 24);
    imageButton->setBounds (248, 152, 40, 40);
    toggleButton->setBounds (224, 64, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void test::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }
    else if (buttonThatWasClicked == imageButton)
    {
        //[UserButtonCode_imageButton] -- add your button handler code here..
        //[/UserButtonCode_imageButton]
    }
    else if (buttonThatWasClicked == toggleButton)
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="test" componentName="" parentClasses="public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
    <IMAGE pos="124 148 100 100" resource="BinaryData::meccanoid_png" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <TEXTEDITOR name="new text editor" id="a4c1fc3f10c8a7e1" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="56 24 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="7fc6a99161faa4a5" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="224 24 150 24" bgColOff="ffffbbfb"
              buttonText="new button" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <IMAGEBUTTON name="new button2" id="c3b1cff7837accc2" memberName="imageButton"
               virtualName="" explicitFocusOrder="0" pos="248 152 40 40" buttonText="new button2"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::led_off_png" opacityNormal="1" colourNormal="ffce3838"
               resourceOver="BinaryData::led_on_png" opacityOver="1" colourOver="0"
               resourceDown="BinaryData::led_on_png" opacityDown="1" colourDown="0"/>
  <TOGGLEBUTTON name="new toggle button" id="99832484a7940f4c" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="224 64 150 24" buttonText="new toggle button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
