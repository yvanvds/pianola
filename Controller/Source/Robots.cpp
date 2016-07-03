/*
  ==============================================================================

    Robots.cpp
    Created: 25 Jun 2016 4:59:11pm
    Author:  yvan

  ==============================================================================
*/

#include "Robots.h"
#include "JuceHeader.h"

robots & Robots() {
  static robots r;
  return r;
}

robots::robots() {
  XmlDocument doc(File::getCurrentWorkingDirectory().getChildFile("config.xml"));
  ScopedPointer<XmlElement> xml(doc.getDocumentElement());

  if (xml == nullptr) {
    AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon
        , "Warning"
        , "No config.xml file present"
    );
    return;
  }

  XmlElement * child = xml->getFirstChildElement();

  while (child != nullptr) {
    String tag = child->getTagName();
    if (child->getTagName() == "meccanoids") {
      loadMeccanoids(child);
    }

    child = child->getNextElement();
  }
}

void robots::loadMeccanoids(XmlElement * content) {
  XmlElement * child = content->getFirstChildElement();

  while (child != nullptr) {
    String name = child->getTagName();
    Meccanoid * m = addMeccanoid(name);

    XmlElement * elm = child->getFirstChildElement();
    while (elm != nullptr) {
      if (elm->getTagName() == "pin") {
        int pin = elm->getIntAttribute("id");
        String name = elm->getStringAttribute("name");
        m->setPinStatus(pin, true);
        m->setPinName(pin, name);
      }
      elm = elm->getNextElement();
    }

    child = child->getNextElement();
  }
}

void robots::loadPoses(XmlElement * content) {

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

void robots::update() {
  for (int i = 0; i < meccanoids.size(); i++) {
    meccanoids[i]->update();
  }
}