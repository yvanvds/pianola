/*
  ==============================================================================

    MeccaBox.cpp
    Created: 12 Jun 2016 5:56:59pm
    Author:  yvan

  ==============================================================================
*/

#include "MeccaBox.h"
#include "MonitorWindow.h"
#include "MeccaConfigWindow.h"
#include "Robots.h"

MeccaBox::MeccaBox(Meccanoid * ptr)
  : image(nullptr)
  , nameLabel(new Label)
  , initButton(nullptr)
  , meccaPtr(ptr)
{
  image = Drawable::createFromImageData(BinaryData::meccanoid_png, BinaryData::meccanoid_pngSize);

  nameLabel->setText(ptr->getName(), dontSendNotification);
  this->addAndMakeVisible(nameLabel);

  initButton = new ImageButton("init");
  initButton->setImages(false, true, true,
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
    ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000)
  );
  initButton->addListener(this);
  this->addAndMakeVisible(initButton);

}

void MeccaBox::resized() {
  nameLabel->setBounds(60, 5, 200, 40);
  initButton->setBounds(275, 5, 20, 20);
}

void MeccaBox::paint(Graphics & g) {
  if (meccaPtr == nullptr || !meccaPtr->isConnected()) {
    g.fillAll(Colours::indianred);
  }
  else {
    g.fillAll(Colours::lightgreen);
 }
  
  if (image.get() != nullptr) {
    image->drawWithin(g, Rectangle<float>(5, 5, 50, 50), RectanglePlacement::centred, 1.f);
  }
}

void MeccaBox::handleAsyncUpdate() {
  repaint();
}

void MeccaBox::update() {
  int lastSeen = meccaPtr->getLastSeen();
  nameLabel->setText(meccaPtr->getName() + " (" + String(lastSeen) + ")", dontSendNotification);
  triggerAsyncUpdate();
}

void MeccaBox::buttonClicked(Button * buttonThatWasClicked) {
  if (buttonThatWasClicked == initButton) {
    meccaPtr->initialize();
  }
}