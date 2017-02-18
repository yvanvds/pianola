#include "ClipLauncher.h"

std::vector<clipLauncher*> clipLaunchers;

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv) {
  DECLARE_T;
  T->active = false;

  if (argc < 2) {
    object_post((t_object *)T, "I need two arguments (column and row).");
    return T;
  }

  T->x = (int)atom_getlong(argv);
  T->y = (int)atom_getlong(argv + 1);
  T->intOut = intout((t_object *)T);

  clipLaunchers.push_back(T);
  return T;
}

void CLASSMETHOD(Free)(IMPORT_T) {
  for (auto it = clipLaunchers.begin(); it != clipLaunchers.end(); it++) {
    if (*it == T) {
      clipLaunchers.erase(it);
      return;
    }
  }
}

void CLASSMETHOD(Send)(IMPORT_T, long n) {
  if (!T->active) return;
  outlet_int(T->intOut, n);
}

void CLASSMETHOD(Toggle)(IMPORT_T, long n) {
  if (n == 0) T->active = false;
  else T->active = true;
}