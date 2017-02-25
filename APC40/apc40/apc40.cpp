#include "ClipLauncher.h"
#include "Slider.h"
#include "KnobManager.h"
#include "ButtonManager.h"
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

  ButtonManager.allOff();
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
      CLASSMETHOD(HandleNoteOff)(T);
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
    post("Clip Led messages must have 3 integers: column - row - mode");
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

void CLASSMETHOD(ClipMode)(IMPORT_T, t_symbol *s, long argc, t_atom *argv)
{
  if (argc != 3) {
    post("Clip Led messages must have 3 parts: column - row - mode");
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

  if (atom_gettype(argv + 2) == A_LONG) {
    int mode = (int)atom_getlong(argv + 2);
    switch (mode) {
      case 0: T->memory.setClipMode(column, row, CM_OFF); break;
      case 1: T->memory.setClipMode(column, row, CM_SINGLE_ORANGE_GREEN); break;
      case 2: T->memory.setClipMode(column, row, CM_SINGLE_ORANGE_RED); break;
      case 3: T->memory.setClipMode(column, row, CM_TOGGLE_ORANGE_GREEN); break;
      case 4: T->memory.setClipMode(column, row, CM_TOGGLE_ORANGE_RED); break;
      case 5: T->memory.setClipMode(column, row, CM_CUSTOM); break;
      default: {
        post("Third argument is not a valid integer");
        return;
      }
    }

  }
  else {
    post("Third argument is not an integer");
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
    T->memory.setClipMode(i, row - 1, (CLIP_MODE)value);
    CLASSMETHOD(SendNoteOn)(T, i + 1, 53 + row - 1, T->memory.getClipLed(i, row - 1));
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

  if (K_ID != K_INVALID && S_ID != S_INVALID) {
    KnobManager.setStyle(K_ID, S_ID);
    CLASSMETHOD(SendCTRL)(T, 1, GetKnobLedCTRL(K_ID), GetKnobStyleCTRL(S_ID));
  }
  else {
    post("Invalid knobstyle message");
  }
}

void CLASSMETHOD(ActivateButton)(IMPORT_T, t_symbol *s, long argc, t_atom *argv)
{
  if (argc < 2) {
    object_post((t_object *)T, "ActivateButton needs 2 arguments");
    return;
  }

  if (argv->a_type == A_SYM) {
    std::string s; s = atom_getsym(argv)->s_name;
    BUTTON b = B_INVALID;
    if (s == "scene1") b = B_SCENE1;
    else if (s == "scene2") b = B_SCENE2;
    else if (s == "scene3") b = B_SCENE3;
    else if (s == "scene4") b = B_SCENE4;
    else if (s == "scene5") b = B_SCENE5;
    else if (s == "stop") b = B_STOP;
    else if (s == "stopall") b = B_STOPALL;
    else if (s == "track1") b = B_TRACK1;
    else if (s == "track2") b = B_TRACK2;
    else if (s == "track3") b = B_TRACK3;
    else if (s == "track4") b = B_TRACK4;
    else if (s == "track5") b = B_TRACK5;
    else if (s == "track6") b = B_TRACK6;
    else if (s == "track7") b = B_TRACK7;
    else if (s == "track8") b = B_TRACK8;
    else if (s == "activator1") b = B_ACT1;
    else if (s == "activator2") b = B_ACT2;
    else if (s == "activator3") b = B_ACT3;
    else if (s == "activator4") b = B_ACT4;
    else if (s == "activator5") b = B_ACT5;
    else if (s == "activator6") b = B_ACT6;
    else if (s == "activator7") b = B_ACT7;
    else if (s == "activator8") b = B_ACT8;
    else if (s == "solo1") b = B_SOLO1;
    else if (s == "solo2") b = B_SOLO2;
    else if (s == "solo3") b = B_SOLO3;
    else if (s == "solo4") b = B_SOLO4;
    else if (s == "solo5") b = B_SOLO5;
    else if (s == "solo6") b = B_SOLO6;
    else if (s == "solo7") b = B_SOLO7;
    else if (s == "solo8") b = B_SOLO8;
    else if (s == "record1") b = B_REC1;
    else if (s == "record2") b = B_REC2;
    else if (s == "record3") b = B_REC3;
    else if (s == "record4") b = B_REC4;
    else if (s == "record5") b = B_REC5;
    else if (s == "record6") b = B_REC6;
    else if (s == "record7") b = B_REC7;
    else if (s == "record8") b = B_REC8;
    else if (s == "pan") b = B_PAN;
    else if (s == "senda") b = B_SENDA;
    else if (s == "sendb") b = B_SENDB;
    else if (s == "sendc") b = B_SENDC;
    else if (s == "clip") b = B_CLIP;
    else if (s == "device") b = B_DEVICE;
    else if (s == "left") b = B_ARROW_LEFT;
    else if (s == "right") b = B_ARROW_RIGHT;
    else if (s == "detail") b = B_DETAIL;
    else if (s == "quantize") b = B_QUANTIZE;
    else if (s == "midi") b = B_OVERDUB;
    else if (s == "metronome") b = B_METRONOME;

    if (b != B_INVALID) {
      post("Invalid activate name");
      return;
    }
    else {
      ButtonManager.setActive(b, (int)atom_getlong(argv + 1));
    }


  }
}

void CLASSMETHOD(HandleNoteOn)(IMPORT_T) {
  if (T->curVal1 >= 53 && T->curVal1 < 58) {
    // clip launch button

    int row = T->curVal1 - 53;
    int column = T->curChannel - 1;
    int outputvalue = 0;

    switch (T->memory.getClipMode(column, row)) {
      case CM_SINGLE_ORANGE_GREEN: {
        T->memory.setClipLed(column, row, CL_GREEN);
        outputvalue = 1;
        break;
      }
      case CM_SINGLE_ORANGE_RED: {
        T->memory.setClipLed(column, row, CL_RED);
        outputvalue = 1;
      }
      case CM_TOGGLE_ORANGE_RED:
      case CM_TOGGLE_ORANGE_GREEN: {
        outputvalue = T->memory.toggle(column, row) ? 1 : 0;
        break;
      }
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

  // try another note event
  BUTTON b = NoteToButton(T->curVal1);
  if (b != B_INVALID) {
    if (b == B_STOP1 || b == B_TRACK1
      || b == B_ACT1 || b == B_SOLO1
      || b == B_REC1) {

      b = (BUTTON)(b + (T->curChannel - 1));
      ButtonManager.trigger(b);
      
      // send led color
      int value = ButtonManager.getValue(b);
      CLASSMETHOD(SendNoteOn)(T, T->curChannel, T->curVal1, value);

    }
    else if (ButtonManager.isToggle(b)) {
      ButtonManager.trigger(b);

      // send led color
      int value = ButtonManager.getValue(b);
      CLASSMETHOD(SendNoteOn)(T, T->curChannel, T->curVal1, value);
    }
    else {
      ButtonManager.trigger(b);
    }
  }
}

void CLASSMETHOD(HandleNoteOff)(IMPORT_T) {
  if (T->curVal1 >= 53 && T->curVal1 < 58) {
    // clip launch button

    int row = T->curVal1 - 53;
    int column = T->curChannel - 1;
    int outputvalue = 0;

    switch (T->memory.getClipMode(column, row)) {
      case CM_SINGLE_ORANGE_RED:
      case CM_SINGLE_ORANGE_GREEN: {
        T->memory.setClipLed(column, row, CL_ORANGE);
        // send led color
        CLASSMETHOD(SendNoteOn)(T, T->curChannel, T->curVal1, (int)T->memory.getClipLed(column, row));

        // send to outputs
        for (int i = 0; i < clipLaunchers.size(); i++) {
          if (clipLaunchers[i]->x == column + 1 && clipLaunchers[i]->y == row + 1) {
            clipLauncherSend(clipLaunchers[i], outputvalue);
          }
        }
      }
      break;
    }

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

void CLASSMETHOD(SendCTRL)(IMPORT_T, int channel, int ctrl, int value) {
  outlet_int(T->intOut, 175 + channel);
  outlet_int(T->intOut, ctrl);
  outlet_int(T->intOut, value);
}