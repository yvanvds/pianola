#include "ButtonManager.h"

buttonManager ButtonManager;

void buttonManager::add(button * obj) {
  bi[obj->ID].buttons.push_back(obj);
}

void buttonManager::remove(button * obj) {
  std::vector<button*> & cur = bi[obj->ID].buttons;
  for (std::vector<button*>::size_type i = 0; i < cur.size(); ) {
    if (cur[i] == obj) {
      cur.erase(cur.begin() + i);
      return;
    }
    else {
      i++;
    }
  }
}

void buttonManager::setValue(BUTTON target, int value) {
  bi[target].currentValue = value;
  std::vector<button*> & cur = bi[target].buttons;

  for (auto it = cur.begin(); it != cur.end(); it++) {
    buttonSend(*it, value);
  }
}