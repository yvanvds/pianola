#include "ClipLauncher.h"

std::vector<clipLauncher*> clipLaunchers;

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv) {
  DECLARE_T;

  if (argc < 2) {
    object_post((t_object *)T, "I need two arguments (row and column).");
    return T;
  }

  T->x = atom_getlong(argv);
  T->y = atom_getlong(argv + 1);
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
  outlet_int(T->intOut, n);
}