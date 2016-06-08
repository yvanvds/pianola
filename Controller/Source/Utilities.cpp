/*
  ==============================================================================

    Utilities.cpp
    Created: 8 Jun 2016 7:26:02pm
    Author:  yvan

  ==============================================================================
*/

#include "Utilities.h"

void OSCTokenize(Array<String> & tokens, const String & string) {
  tokens.clear();
  if (!string.length()) return;

  String token;
  for (int i = 0; i < string.length(); i++) {
    if (string[i] == '/') {
      tokens.add(token);
      token.clear();
    } else {
      token += string[i];
    }
  }
  tokens.add(token);
}