/*
  ==============================================================================

    VirtualBox.h
    Created: 18 Sep 2016 4:42:41pm
    Author:  yvan

  ==============================================================================
*/

#ifndef VIRTUALBOX_H_INCLUDED
#define VIRTUALBOX_H_INCLUDED

#include "JuceHeader.h"
#include "VirtualBot.h"

class VirtualBox : public Component, private AsyncUpdater, public ButtonListener {
public:
	VirtualBox(VirtualBot * ptr);

	virtual void resized() override;
	virtual void paint(Graphics & g) override;

	void update();

	void buttonClicked(Button * buttonThatWasClicked) override;
	void handleAsyncUpdate() override;

private:
	ScopedPointer<Drawable> image;
	ScopedPointer<Label> nameLabel;
	ScopedPointer<Label> ipLabel;
	ScopedPointer<Label> portLabel;
	ScopedPointer<ImageButton> initButton;

	String name;
	VirtualBot * virtualPtr;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VirtualBox);
};



#endif  // VIRTUALBOX_H_INCLUDED
