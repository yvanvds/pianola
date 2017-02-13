#include "KnobManager.h"

knobManager KnobManager;

void knobManager::add(knob * obj)
{
  ki[obj->ID].knobs.push_back(obj);
}

void knobManager::remove(knob * obj)
{
  std::vector<knob*> & cur = ki[obj->ID].knobs;
  for (std::vector<knob*>::size_type i = 0; i < cur.size(); ) {
    if (cur[i] == obj) {
      cur.erase(cur.begin() + i);
      return;
    }
    else {
      i++;
    }
  }
}

void knobManager::setStyle(KNOB target, KNOB_STYLE style)
{
  ki[target].style = style;
}

void knobManager::setValue(KNOB target, int value)
{
  if (ki[target].style == KS_PAN) value -= 64;

  ki[target].currentValue = value;
  std::vector<knob*> & cur = ki[target].knobs;
 
  for (auto it = cur.begin(); it != cur.end(); it++) {   
    knobSend(*it, value);
  }
}






