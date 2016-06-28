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
#include "JuceHeader.h"

class Meccanoid : public Robot {
public:
  Meccanoid();

  virtual void handleMessage(const Array<String> & tokens, const OSCMessage & message);

  void initialize();

  bool           getPinStatus(int pin); Meccanoid & setPinStatus(int pin, bool           status);
  const String & getPinName  (int pin); Meccanoid & setPinName  (int pin, const String & name  );
  int            getPin(const String & name); // uses offset!!!

private:

  bool pinStatus[13];
  String pinName[13];

};



#endif  // MECCANOID_H_INCLUDED
