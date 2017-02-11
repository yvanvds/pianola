#pragma once
#include "Knob.h"
#include <vector>



class knobManager {
public:
  void add(knob * obj);
  void remove(knob * obj);

  void setStyle(KNOB target, KNOB_STYLE style);
  void setValue(KNOB target, int value);

private:
  struct knobInfo {
    int currentValue;
    KNOB_STYLE style = KS_OFF;
    std::vector<knob*> knobs;
  };

  knobInfo ki[K_INVALID];
};

extern knobManager KnobManager;
