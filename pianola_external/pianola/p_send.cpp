#include "p_send.h"

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom * argv) {
  DECLARE_T;
  T->id = I_NONE;
  T->part = RP_NONE;
  T->behaviour = B_NONE;
  T->valid = true;

  // first argument should be the destination robot
  if (argc > 0) {
    if ((argv)->a_type == A_SYM) {
      object_post((t_object *)T, "First argument is %s", atom_getsym(argv)->s_name);
      T->id = toIdentity(atom_getsym(argv)->s_name);
    }
    else T->id = I_INVALID;

    if (T->id == I_INVALID) {
      object_post((t_object *)T, "First argument (identity) is invalid");
      T->valid = false;
    }
  }

  // second argument sets the destination robot part
  if (argc > 1) {
    if ((argv + 1)->a_type == A_SYM) {
      T->part = toRobotPart(atom_getsym(argv + 1)->s_name);
    }
    else T->part = RP_INVALID;

    if (T->part == RP_INVALID) {
      object_post((t_object *)T, "Second argument (part) is invalid");
      T->valid = false;
    }
  }

  // third part when second is behaviour
  if (T->part == RP_BEHAVIOUR && argc > 2) {
    if ((argv + 2)->a_type == A_SYM) {
      T->behaviour = toBehaviour(atom_getsym(argv + 2)->s_name);
    }
    else T->behaviour = B_INVALID;

    if (T->behaviour == B_INVALID) {
      object_post((t_object *)T, "Third argument (behaviour) is invalid");
      T->valid = false;
    }
  }

  return T;
}

void CLASSMETHOD(Int)(IMPORT_T, long n) {
  if (T->valid) {
    N.send(T, n);
  }
  else {
    object_post((t_object *)T, "Failed to send int on invalid object");
  }
}

void CLASSMETHOD(Float)(IMPORT_T, float f) {
  if (T->valid) {
    N.send(T, f);
  }
  else {
    object_post((t_object *)T, "Failed to send float on invalid object");
  }
}

void CLASSMETHOD(Bang)(IMPORT_T) {
  N.sendTest();
}