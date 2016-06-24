/*
  ==============================================================================

    outputBox.cpp
    Created: 12 Jun 2016 5:56:59pm
    Author:  yvan

  ==============================================================================
*/

#include "outputBox.h"
#include "MonitorWindow.h"
#include "RobotConfigWindow.h"

OutputBox::OutputBox(IDENTITY identity)
  : image(nullptr)
  , name(new Label)
  , initButton(nullptr)
  , identity(identity)
{
  image = Drawable::createFromImageData(BinaryData::meccanoid_png, BinaryData::meccanoid_pngSize);

  name->setText(toString(identity), dontSendNotification);
  this->addAndMakeVisible(name);

  initButton = new ImageButton("init");
  initButton->setImages(false, true, true,
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000)
  );
  initButton->addListener(this);
  this->addAndMakeVisible(initButton);

}

void OutputBox::resized() {
  name->setBounds(60, 5, 200, 40);
  initButton->setBounds(275, 5, 20, 20);
}

void OutputBox::paint(Graphics & g) {
  Robot * robot = WindowPtr->getRobot(identity);
  if (robot == nullptr || !robot->isConnected()) {
    g.fillAll(Colours::indianred);
  }
  else {
    g.fillAll(Colours::lightgreen);
 }
  
  if (image.get() != nullptr) {
    image->drawWithin(g, Rectangle<float>(5, 5, 50, 50), RectanglePlacement::centred, 1.f);
  }
}

void OutputBox::handleAsyncUpdate() {
  
  repaint();
}

void OutputBox::update() {
  Robot * robot = WindowPtr->getRobot(identity);
  if (robot != nullptr) {
    int lastSeen = robot->getLastSeen();
    name->setText(toString(identity) + " (" + String(lastSeen) + ")", dontSendNotification);
  }
  triggerAsyncUpdate();
}

void OutputBox::buttonClicked(Button * buttonThatWasClicked) {
  if (buttonThatWasClicked == initButton) {
    RobotConfigWindow * window = new RobotConfigWindow(WindowPtr->getRobot(identity));
    CallOutBox::launchAsynchronously(window, initButton->getScreenBounds(), nullptr);
    //Robot * robot = WindowPtr->getRobot(identity);
    //if (robot != nullptr && robot->isConnected()) {
    //  juce::OSCMessage message("/" + robot->getName() + "/init");
    //  robot->send(message);
    //}
  }
}