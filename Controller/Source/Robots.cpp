/*
  ==============================================================================

    Robots.cpp
    Created: 25 Jun 2016 4:59:11pm
    Author:  yvan

  ==============================================================================
*/

#include "Robots.h"
#include "JuceHeader.h"
#include "Servo.h"

robots & Robots() {
  static robots r;
  return r;
}

robots::robots() {
  reloadConfig();
}

void robots::reloadConfig()
{
  File config = File::getSpecialLocation(juce::File::SpecialLocationType::currentApplicationFile);
  config = config.getParentDirectory();
  config = config.getChildFile("config.xml");
  XmlDocument doc(config);
  ScopedPointer<XmlElement> xml(doc.getDocumentElement());

  if (xml == nullptr) {
    AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon
      , "Warning"
      , "Missing file: " + config.getFullPathName()
    );
    return;
  }

  XmlElement * child = xml->getFirstChildElement();

  while (child != nullptr) {
    String tag = child->getTagName();
    if (child->getTagName() == "meccanoids") {
      loadMeccanoids(child);
    }

	if (child->getTagName() == "virtual") {
		loadVirtuals(child);
	}

    child = child->getNextElement();
  }
}

void robots::loadMeccanoids(XmlElement * content) {
  XmlElement * child = content->getFirstChildElement();

  while (child != nullptr) {

    // get named meccanoid or create one
    String name = child->getTagName();
    Meccanoid * m = getMeccanoid(name);
    if (m == nullptr) {
      m = addMeccanoid(name);
    }
    
    // reset all values
    m->resetServos();

    XmlElement * elm = child->getFirstChildElement();
    while (elm != nullptr) {
      if (elm->getTagName() == "servo") {
        int ID = elm->getIntAttribute("id");
        String name = elm->getStringAttribute("name");

        Servo * s = m->getServo(ID);
        if (s != nullptr) {
          
          s->setStatus(true);
          if (elm->hasAttribute("name")) {
            s->setName(elm->getStringAttribute("name"));
          }
          if (elm->hasAttribute("reverse")) {
            s->setReverse(elm->getBoolAttribute("reverse"));
          }
          if (elm->hasAttribute("min")) {
            s->setMin(elm->getIntAttribute("min"));
          }
          if (elm->hasAttribute("max")) {
            s->setMax(elm->getIntAttribute("max"));
          }
        }
      }
      elm = elm->getNextElement();
    }

    child = child->getNextElement();
  }
}

void robots::loadPoses(XmlElement * content) {
	
}

void robots::loadVirtuals(XmlElement * content) {
	XmlElement * child = content->getFirstChildElement();

	while (child != nullptr) {

		// get named virtual or create one
		String name = child->getTagName();
		VirtualBot * v = getVirtualBot(name);
		if (v == nullptr) {
			v = addVirtualBot(name);
		}

		child = child->getNextElement();
	}
}

Meccanoid * robots::addMeccanoid(const String & name) {
  Meccanoid * m = meccanoids.add(new Meccanoid());
  m->setName(name);
  return m;
}

Meccanoid * robots::getMeccanoid(const String & name) {
  for (int i = 0; i < meccanoids.size(); i++) {
    if (meccanoids[i]->getName() == name) return meccanoids[i];
  }
  return nullptr;
}

Meccanoid * robots::getMeccanoid(int idx) {
  return meccanoids[idx];
}

VirtualBot * robots::addVirtualBot(const String & name) {
	VirtualBot * v = virtualbots.add(new VirtualBot());
	v->setName(name);
	return v;
}

VirtualBot * robots::getVirtualBot(const String & name) {
	for (int i = 0; i < virtualbots.size(); i++) {
		if (virtualbots[i]->getName() == name) return virtualbots[i];
	}
	return nullptr;
}

VirtualBot * robots::getVirtualBot(int idx) {
	return virtualbots[idx];
}

Robot * robots::getRobot(const String & name) {
	Robot * result = getMeccanoid(name);
	if (result == nullptr) {
		result = getVirtualBot(name);
	}
	return result;
}

void robots::update() {
  for (int i = 0; i < meccanoids.size(); i++) {
    meccanoids[i]->update();
  }

  for (int i = 0; i < virtualbots.size(); i++) {
	  virtualbots[i]->update();
  }
}