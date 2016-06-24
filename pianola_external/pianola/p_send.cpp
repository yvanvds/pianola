#include "p_send.h"
#include "juce_core.h"

CREATECLASSPTR;

void * CLASSMETHOD(New)(t_symbol * s, long argc, t_atom * argv) {
  DECLARE_T;
  T->id0 = gensym("");
  T->id1 = gensym("");

  if (argc < 1) {
    object_post((t_object *)T, "Please specify a robot");
  }

  // first argument should be the destination robot
  if (argc > 0) {
    if ((argv)->a_type == A_SYM) {
      T->id0 = atom_getsym(argv);
    }
    else {
      object_post((t_object *)T, "First argument (identity) is invalid");
    }
  }

  // second argument sets the destination robot part
  if (argc > 1) {
    if ((argv + 1)->a_type == A_SYM) {
      T->id1 = atom_getsym(argv + 1);
    }
    else {
      object_post((t_object *)T, "Second argument (pin name) is invalid");
    }
  }

  return T;
}


void CLASSMETHOD(Joint)(IMPORT_T, t_symbol * s, long argc, t_atom *argv) {
  if (T->id0 == gensym("")) {
    object_post((t_object *)T, "Please specify a robot.");
  }

  if (T->id1 == gensym("")) {
    object_post((t_object *)T, "No body part is specified.");
  }

  if (argc != 3) {
    post("Joint messages must have 3 arguments: joint [0-3], position [24-232] and duration(millis).");
    return;
  }
  
  int joint    = 0;
  int position = 0;
  int duration = 0;
  
  if (atom_gettype(argv) == A_LONG) {
    joint = (int)atom_getlong(argv);
  }
  else {
    post("First argument is not an integer.");
    return;
  }

  if (atom_gettype(argv + 1) == A_LONG) {
    position = (int)atom_getlong(argv + 1);
  }
  else {
    post("Second argument is not an integer.");
    return;
  }
  
  if (atom_gettype(argv + 2) == A_LONG) {
    duration = (int)atom_getlong(argv + 2);
  }
  else {
    post("Third argument is not an integer.");
    return;
  }

  N.sendJoint(T, joint, position, duration);
}