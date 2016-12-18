/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Enums.h"

static ScopedPointer<ApplicationCommandManager> applicationCommandManager;

//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
	mlaf = new MuteLookAndFeel();
	this->setLookAndFeel(mlaf);

	addAndMakeVisible(menuBar = new MenuBarComponent(this));

	resized();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
	g.fillAll(Colour(50, 50, 50));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	if (mlaf != nullptr) {
		Rectangle<int> area(getLocalBounds());
		menuBar->setBounds(area.removeFromTop(mlaf->getDefaultMenuBarHeight()));
	}
	
}

StringArray MainContentComponent::getMenuBarNames()
{
	const char* const names[] = { "Direct Control", "Samples", "Poses", nullptr };
	return StringArray(names);
}

PopupMenu MainContentComponent::getMenuForIndex(int menuIndex, const String & menuName)
{
	ApplicationCommandManager* commandManager = &MainContentComponent::getApplicationCommandManager();
	
	PopupMenu menu;

	if (menuIndex == 0) {
		menu.addCommandItem(commandManager, CID_SHOWVIR1);
		menu.addCommandItem(commandManager, CID_SHOWVIR2);
		menu.addCommandItem(commandManager, CID_SHOWVIR3);
		menu.addCommandItem(commandManager, CID_SHOWVIR4);
	}

	return menu;
}

void MainContentComponent::menuItemSelected(int menuItemId, int idx)
{
}

ApplicationCommandManager & MainContentComponent::getApplicationCommandManager()
{
	if (applicationCommandManager == nullptr)
		applicationCommandManager = new ApplicationCommandManager();

	return *applicationCommandManager;
}
