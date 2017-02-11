#pragma once
#include "ext.h"
#include <vector>

#undef ClassName
#define ClassName clipLauncher
#include "defines.h"

CREATESTRUCT(
  int x; int y;

  // outlet
  void * intOut;
);

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom *argv);
void CLASSMETHOD(Free)(IMPORT_T);

// outlet
void CLASSMETHOD(Send)(IMPORT_T, long n);

// container for all cliplaunchers
extern std::vector<clipLauncher*> clipLaunchers;