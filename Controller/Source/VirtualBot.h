/*
  ==============================================================================

    virtualBot.h
    Created: 18 Sep 2016 4:24:11pm
    Author:  yvan

  ==============================================================================
*/

#ifndef VIRTUALBOT_H_INCLUDED
#define VIRTUALBOT_H_INCLUDED

#include "Robot.h"
#include "JuceHeader.h"
#include "Defines.h"
#include "../../Shared/Messages.h"

class VirtualBot : public Robot {
public:
	VirtualBot();

	virtual void handleMessage(const OSCMessage & message);

	void initialize();

private:
	BODYPART getBodyPart(const String & name);
};



#endif  // VIRTUALBOT_H_INCLUDED
