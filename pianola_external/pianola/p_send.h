#pragma once
#include "ext.h"

#undef ClassName
#define ClassName p_send
#include "defines.h"
#include "Enums.h"

#include "Network.h"

CREATESTRUCT(
  t_symbol * id0;
  t_symbol * id1;
);

void * CLASSMETHOD(New  )(t_symbol * s, long argc, t_atom * argv);
void   CLASSMETHOD(Joint)(IMPORT_T, t_symbol * s, long argc, t_atom *argv);