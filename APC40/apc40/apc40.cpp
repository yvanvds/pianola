#include "ClipLauncher.h"
#include "Slider.h"
#include "KnobManager.h"
#include "apc40.h"
#include <string>


CREATECLASSPTR;

apc40 * APC40 = nullptr;

void * CLASSMETHOD(New)() {
  DECLARE_T;
  if (APC40 == nullptr) {
    APC40 = T;
    T->curMessage = M_NONE;

    T->intOut = intout((t_object *)T);
  }
  else {
    post("You should only have one APC40 box active at any time!");
  }

  return T;
}

void CLASSMETHOD(Free)(IMPORT_T)
{
  APC40 = nullptr;
}

void CLASSMETHOD(Reset)(IMPORT_T) {
  // set midi port
  //t_atom argv[1];
  //atom_setsym(argv, gensym("\"Akai APC40\""));
  //outlet_list(T->messageOut, gensym("port"), 1, argv);

  // send sysex for apc mode 1
  outlet_int(T->intOut, 240);
  outlet_int(T->intOut, 71);
  outlet_int(T->intOut, 0);
  outlet_int(T->intOut, 115);
  outlet_int(T->intOut, 96);
  outlet_int(T->intOut, 0);
  outlet_int(T->intOut, 4);
  outlet_int(T->intOut, 65);
  outlet_int(T->intOut, 0);
  outlet_int(T->intOut, 0);
  outlet_int(T->intOut, 0);
  outlet_int(T->intOut, 247);
}

void CLASSMETHOD(inletInt)(IMPORT_T, long n) {
  if (T->curMessage == M_NONE) {
    if (n >= 144 && n < 161) {
      T->curMessage = M_NOTEON;
      T->curChannel = n - 143;
      T->curStep = 0;
      return;
    }
    if (n >= 128 && n < 144) {
      T->curMessage = M_NOTEOFF;
      T->curChannel = n - 127;
      T->curStep = 0;
      return;
    }
    if (n >= 176 && n < 183) {
      T->curMessage = M_CTRL;
      T->curChannel = n - 175;
      T->curStep = 0;
      return;
    }
  }

  if (T->curMessage == M_NOTEON) {
    if (T->curStep == 0) {
      T->curVal1 = n;
      T->curStep = 1;
      return;
    }
    if (T->curStep == 1) {
      T->curVal2 = n;
      CLASSMETHOD(HandleNoteOn)(T);
      T->curMessage = M_NONE;
      return;
    }
  }

  if (T->curMessage == M_NOTEOFF) {
    if (T->curStep == 0) {
      T->curVal1 = n;
      T->curStep = 1;
      return;
    }
    if (T->curStep == 1) {
      T->curVal2 = n;
      T->curMessage = M_NONE;
      return;
    }
  }

  if (T->curMessage == M_CTRL) {
    if (T->curStep == 0) {
      T->curVal1 = n;
      T->curStep = 1;
      return;
    }
    if (T->curStep == 1) {
      T->curVal2 = n;
      CLASSMETHOD(HandleCTRL)(T);
      T->curMessage = M_NONE;
      return;
    }
  }


}

void CLASSMETHOD(ClipLed)(IMPORT_T, t_symbol *s, long argc, t_atom *argv)
{
  if (argc != 3) {
    post("Clip Led messages must have 3 parts: column - row - color");
    return;
  }

  int row, column;
  CLIP_LED cl = CL_INVALID;

  if (atom_gettype(argv) == A_LONG) {
    column = (int)atom_getlong(argv);
  }
  else {
    post("First argument is not an integer.");
    return;
  }

  if (atom_gettype(argv + 1) == A_LONG) {
    row = (int)atom_getlong(argv + 1);
  }
  else {
    post("Second argument is not an integer.");
    return;
  }

  if (row < 1 || row > CLIPROWS || column < 1 || column > CLIPCOLUMNS) {
    post("Element is not in range.");
    return;
  }

  // set array offset
  row--; column--;

  if (atom_gettype(argv + 2) == A_SYM) {
    std::string s; 
    s = atom_getsym(argv + 2)->s_name;
    if (s == "green") T->memory.setClipLed(column, row, CL_GREEN);
    else if (s == "orange") T->memory.setClipLed(column, row, CL_ORANGE);
    else if (s == "red") T->memory.setClipLed(column, row, CL_RED);
    else {
      post("Third argument is not a valid symbol");
      return;
    }
  }
  else {
    post("Third argument is not a symbol");
    return;
  }

  // send led color to apc
  {
    CLASSMETHOD(SendNoteOn)(T, column + 1, row + 53, (int)T->memory.getClipLed(column, row));
  }
}

void CLASSMETHOD(ClipRow)(IMPORT_T, t_symbol * s, long argc, t_atom *argv) {
  if (argc != 9) {
    post("ClipRow messages must have nine numbers");
    return;
  }

  int row;
  if (atom_gettype(argv) == A_LONG) {
    row = (int)atom_getlong(argv);
  }
  else {
    post("First argument is not an integer.");
    return;
  }

  for (int i = 0; i < 8; i++) {
    int value = (int)atom_getlong(argv + 1 + i);
    T->memory.setClipLed(i, row - 1, (CLIP_LED)value);
    CLASSMETHOD(SendNoteOn)(T, i + 1, 53 + row - 1, value);
  }
}

void CLASSMETHOD(KnobStyle)(IMPORT_T, t_symbol *s, long argc, t_atom *argv)
{
  if (argc != 3) {
    post("KnobStyle messages need three arguments");
    return;
  }

  KNOB K_ID = K_INVALID;
  std::string name; name = atom_getsym(argv)->s_name;
  int id = (int)atom_getlong(argv + 1);
  std::string style; style = atom_getsym(argv + 2)->s_name;
  
  switch (id) {
    case 1: name == "track" ? K_ID = K_TRACK1 : K_ID = K_DEVICE1; break;
    case 2: name == "track" ? K_ID = K_TRACK2 : K_ID = K_DEVICE2; break;
    case 3: name == "track" ? K_ID = K_TRACK3 : K_ID = K_DEVICE3; break;
    case 4: name == "track" ? K_ID = K_TRACK4 : K_ID = K_DEVICE4; break;
    case 5: name == "track" ? K_ID = K_TRACK5 : K_ID = K_DEVICE5; break;
    case 6: name == "track" ? K_ID = K_TRACK6 : K_ID = K_DEVICE6; break;
    case 7: name == "track" ? K_ID = K_TRACK7 : K_ID = K_DEVICE7; break;
    case 8: name == "track" ? K_ID = K_TRACK8 : K_ID = K_DEVICE8; break;
  }

  KNOB_STYLE S_ID = KS_INVALID;
  if (style == "off") S_ID = KS_OFF;
  else if (style == "single") S_ID = KS_SINGLE;
  else if (style == "volume") S_ID = KS_VOLUME;
  else if (style == "pan") S_ID = KS_PAN;

  KnobManager.setStyle(K_ID, S_ID);
}

void CLASSMETHOD(HandleNoteOn)(IMPORT_T) {
  if (T->curVal1 >= 53 && T->curVal1 < 58) {
    // clip launch button

    int row = T->curVal1 - 53;
    int column = T->curChannel - 1;
    int outputvalue = 0;

    switch (T->memory.getClipLed(column, row)) {
      case CL_GREEN: T->memory.setClipLed(column, row, CL_ORANGE); outputvalue = 0; break;
      case CL_ORANGE: T->memory.setClipLed(column, row, CL_GREEN); outputvalue = 1; break;
    }

    // send led color
    CLASSMETHOD(SendNoteOn)(T, T->curChannel, T->curVal1, (int)T->memory.getClipLed(column, row));
    
    // send to outputs
    for (int i = 0; i < clipLaunchers.size(); i++) {
      if (clipLaunchers[i]->x == column + 1 && clipLaunchers[i]->y == row + 1) {
        clipLauncherSend(clipLaunchers[i], outputvalue);
      }
    }
    return;
  }
}

void CLASSMETHOD(HandleCTRL)(IMPORT_T) {
  SLIDER SID = S_INVALID;
  KNOB KID = K_INVALID;

  if (T->curVal1 == 7) {
    switch (T->curChannel) {
      case 1: SID = S_1; break;
      case 2: SID = S_2; break;
      case 3: SID = S_3; break;
      case 4: SID = S_4; break;
      case 5: SID = S_5; break;
      case 6: SID = S_6; break;
      case 7: SID = S_7; break;
      case 8: SID = S_8; break;
    }
  }

  else if (T->curVal1 == 14) SID = S_MASTER;
  else if (T->curVal1 == 15) SID = S_PAN;

  else switch (T->curVal1) {
    case 16: KID = K_DEVICE1; break;
    case 17: KID = K_DEVICE2; break;
    case 18: KID = K_DEVICE3; break;
    case 19: KID = K_DEVICE4; break;
    case 20: KID = K_DEVICE5; break;
    case 21: KID = K_DEVICE6; break;
    case 22: KID = K_DEVICE7; break;
    case 23: KID = K_DEVICE8; break;
    case 47: KID = K_CUE; break;
    case 48: KID = K_TRACK1; break;
    case 49: KID = K_TRACK2; break;
    case 50: KID = K_TRACK3; break;
    case 51: KID = K_TRACK4; break;
    case 52: KID = K_TRACK5; break;
    case 53: KID = K_TRACK6; break;
    case 54: KID = K_TRACK7; break;
    case 55: KID = K_TRACK8; break;
  }

  if (SID != S_INVALID) {
    for (int i = 0; i < Sliders.size(); i++) {
      if (Sliders[i]->ID == SID) {
        sliderSend(Sliders[i], T->curVal2);
      }
    }
  }
  else if (KID != K_INVALID) {
    KnobManager.setValue(KID, T->curVal2);
  }
}

void CLASSMETHOD(SendNoteOn)(IMPORT_T, int channel, int note, int velocity) {
  outlet_int(T->intOut, 143 + channel);
  outlet_int(T->intOut, note);
  outlet_int(T->intOut, velocity);
}
