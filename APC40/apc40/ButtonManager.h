#pragma once
#include "Button.h"
#include <vector>

class buttonManager {
public:
  void add(button * obj);
  void remove(button * obj);

  void setValue(BUTTON target, int value);

private:
  struct buttonInfo {
    int currentValue;
    std::vector<button*> buttons;
  };

  buttonInfo bi[B_INVALID];
};

extern buttonManager ButtonManager;