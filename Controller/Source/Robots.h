/*
  ==============================================================================

    Robots.h
    Created: 25 Jun 2016 4:59:11pm
    Author:  yvan

  ==============================================================================
*/

#ifndef ROBOTS_H_INCLUDED
#define ROBOTS_H_INCLUDED

#include "Meccanoid.h"
#include "virtualBot.h"
#include "JuceHeader.h"

class robots {
public:
  robots();
  Meccanoid * getMeccanoid(      int      idx );
  Meccanoid * getMeccanoid(const String & name);
  Meccanoid * addMeccanoid(const String & name);

  VirtualBot * getVirtualBot(int idx);
  VirtualBot * getVirtualBot(const String & name);
  VirtualBot * addVirtualBot(const String & name);

  Robot * getRobot(const String & name);

  void update();

  int countMeccanoids () { return meccanoids .size(); }
  int countVirtualBots() { return virtualbots.size(); }

  void reloadConfig();

private:
  void loadRobots  (XmlElement * content);
  void loadVirtuals(XmlElement * content);

  OwnedArray<Meccanoid> meccanoids;
  OwnedArray<VirtualBot> virtualbots;
};

robots & Robots();



#endif  // ROBOTS_H_INCLUDED
