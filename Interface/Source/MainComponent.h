/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MuteLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, public MenuBarModel
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

	MuteLookAndFeel * getLookAndFeel() { return mlaf.get(); }

	// main menu
	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int menuIndex, const String& menuName) override;
	void menuItemSelected(int menuItemId, int idx) override;

	// (return the command manager object used to dispatch command events)
	static ApplicationCommandManager& getApplicationCommandManager();
	

private:

    // looks
	ScopedPointer<MuteLookAndFeel> mlaf;

	// main menu
	ScopedPointer<MenuBarComponent> menuBar;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
