/*
  ==============================================================================

    VirtualBox.cpp
    Created: 18 Sep 2016 4:42:41pm
    Author:  yvan

  ==============================================================================
*/

#include "VirtualBox.h"
#include "MonitorWindow.h"
#include "MeccaConfigWindow.h"
#include "Robots.h"

VirtualBox::VirtualBox(VirtualBot * ptr)
	: image(nullptr)
	, nameLabel(new Label)
	, ipLabel(new Label)
	, portLabel(new Label)
	, initButton(nullptr)
	, virtualPtr(ptr)
{
	image = Drawable::createFromImageData(BinaryData::vir_png, BinaryData::vir_pngSize);

	nameLabel->setText(ptr->getName(), dontSendNotification);
	this->addAndMakeVisible(nameLabel);

	ipLabel->setText(String("IP: ") + ptr->getIp(), dontSendNotification);
	this->addAndMakeVisible(ipLabel);

	portLabel->setText(String("Port: ") + String(ptr->getPort()), dontSendNotification);
	this->addAndMakeVisible(portLabel);

	initButton = new ImageButton("init");
	initButton->setImages(false, true, true,
		ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
		ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000),
		ImageCache::getFromMemory(BinaryData::cog_png, BinaryData::cog_pngSize), 1.f, Colour(0x00000000)
	);
	initButton->addListener(this);
	this->addAndMakeVisible(initButton);
}

void VirtualBox::resized() {
	nameLabel->setBounds(60, 5, 200, 40);
	ipLabel->setBounds(60, 25, 200, 40);
	portLabel->setBounds(200, 25, 100, 40);
	initButton->setBounds(275, 5, 20, 20);
}

void VirtualBox::paint(Graphics & g) {
	if (virtualPtr == nullptr || !virtualPtr->isConnected()) {
		g.fillAll(Colour(60, 0, 0));
	}
	else if (virtualPtr->getLastSeen() > 20) {
		g.fillAll(Colour(60, 40, 0));
	}
	else {
		g.fillAll(Colour(0, 60, 0));
	}

	if (image.get() != nullptr) {
		image->drawWithin(g, Rectangle<float>(5, 5, 50, 50), RectanglePlacement::centred, 1.f);
	}
}

void VirtualBox::handleAsyncUpdate() {
	repaint();
}

void VirtualBox::update() {
	int lastSeen = virtualPtr->getLastSeen();
	nameLabel->setText(virtualPtr->getName() + " (" + String(lastSeen) + ")", dontSendNotification);
	ipLabel->setText(String("IP: ") + virtualPtr->getIp(), dontSendNotification);
	portLabel->setText(String("Port: ") + String(virtualPtr->getPort()), dontSendNotification);
	triggerAsyncUpdate();
}

void VirtualBox::buttonClicked(Button * buttonThatWasClicked) {
	if (buttonThatWasClicked == initButton) {
		virtualPtr->initialize();
	}
}
