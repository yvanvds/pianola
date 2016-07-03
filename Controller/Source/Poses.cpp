/*
  ==============================================================================

    Poses.cpp
    Created: 2 Jul 2016 10:36:26pm
    Author:  yvan

  ==============================================================================
*/

#include "Poses.h"

poses & Poses() {
  static poses p;
  return p;
}

poses::poses() {
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
    if (child->getTagName() == "poses") {
      XmlElement * entry = child->getFirstChildElement();

      while (entry != nullptr) {
        addPose(entry);
        entry = entry->getNextElement();
      }
      
    }

    child = child->getNextElement();
  }
}

void poses::addPose(XmlElement * content) {
  Pose * p = list.add(new Pose);
  p->setName(content->getTagName());

  XmlElement * elm = content->getFirstChildElement();
  while (elm != nullptr) {
    if (elm->getTagName() == "action") {
      p->addAction(elm);
    }
    elm = elm->getNextElement();
  }
}

bool poses::sendPoseToRobot(const String & pose, int duration, Meccanoid & robot) {
  for (int i = 0; i < list.size(); i++) {
    if (list[i]->getName() == pose) {
      return list[i]->sendToRobot(duration, robot);
    }
  }
  return false;
}