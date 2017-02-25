#include "ButtonManager.h"
#include "apc40.h"

buttonManager ButtonManager;



buttonManager::buttonManager()
{
  for (int i = 0; i < B_INVALID; i++) {
    bi[i].value = false;
    bi[i].active = true;
    if (i == B_SHIFT || i == B_SELECT_UP || i == B_SELECT_DOWN
      || i == B_SELECT_LEFT || i == B_SELECT_RIGHT || i == B_TAP
      || i == B_NUDGE_MIN || i == B_NUDGE_PLUS || i == B_PLAY
      || i == B_STOP || i == B_REC) {
      bi[i].toggle = false;
    }
    else {
      bi[i].toggle = true;
    }
  }
}

void buttonManager::add(button * obj) {
  if (obj->ID == B_INVALID) return;
  bi[obj->ID].buttons.push_back(obj);
}

void buttonManager::remove(button * obj) {
  if (obj->ID == B_INVALID) return;
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

void buttonManager::setValue(BUTTON target, bool value) {
  if (!bi[target].active) return;
  bi[target].value = value;
  std::vector<button*> & cur = bi[target].buttons;
}

void buttonManager::setActive(BUTTON target, bool value)
{
  bi[target].active = value;
}

int buttonManager::getValue(BUTTON target)
{
  return bi[target].value ? 1 : 0;
}

void buttonManager::trigger(BUTTON target) {
  if (!bi[target].active) return;

  if (bi[target].toggle) {
    if (bi[target].value == true) {
      bi[target].value = false;
    }
    else {
      bi[target].value = true;
    }
    std::vector<button*> & cur = bi[target].buttons;

    for (auto it = cur.begin(); it != cur.end(); it++) {
      buttonSend(*it, bi[target].value ? 1 : 0);
    }
  }
  else {
    std::vector<button*> & cur = bi[target].buttons;

    for (auto it = cur.begin(); it != cur.end(); it++) {
      buttonSend(*it, 1);
    }
  }
}



bool buttonManager::isToggle(BUTTON target)
{
  return bi[target].toggle;
}

void buttonManager::allOff()
{
  for (int i = 0; i < B_INVALID; i++) {
    bi[i].value = false;
    int note = ButtonToNote((BUTTON)i);
    if (note >= 0x30 && note < 0x35) {
      for (int j = 1; j <= 8; j++) {
        apc40SendNoteOn(APC40, j, note, 0);
      }
    }
    else {
      apc40SendNoteOn(APC40, 1, note, 0);
    }
  }
}
