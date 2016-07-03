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
#include "JuceHeader.h"

class robots {
public:
  robots();
  Meccanoid * getMeccanoid(      int      idx );
  Meccanoid * getMeccanoid(const String & name);
  Meccanoid * addMeccanoid(const String & name);

  void update();

  int countMeccanoids() { return meccanoids.size(); }

private:
  void loadMeccanoids(XmlElement * content);
  void loadPoses     (XmlElement * content);  

  OwnedArray<Meccanoid> meccanoids;
};

robots & Robots();



#endif  // ROBOTS_H_INCLUDED
