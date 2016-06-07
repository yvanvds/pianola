/*
  ==============================================================================

    Meccanoid.h
    Created: 7 Jun 2016 7:11:29pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MECCANOID_H_INCLUDED
#define MECCANOID_H_INCLUDED

#include "Robot.h"

class Meccanoid : public Robot {
public:
  virtual void handleMessage(const OSCMessage & message);
};



#endif  // MECCANOID_H_INCLUDED
