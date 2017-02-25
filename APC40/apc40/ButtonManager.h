#pragma once
#include "Button.h"
#include <vector>

class buttonManager {
public:
  buttonManager();

  void add(button * obj);
  void remove(button * obj);

  void setValue(BUTTON target, bool value);
  void setActive(BUTTON target, bool value);
  int getValue(BUTTON target);
  void trigger(BUTTON target);

  bool isToggle(BUTTON target);
  void allOff();

private:
  struct buttonInfo {
    bool value;
    bool toggle;
    bool active;
    std::vector<button*> buttons;
  };

  buttonInfo bi[B_INVALID];
};

extern buttonManager ButtonManager;