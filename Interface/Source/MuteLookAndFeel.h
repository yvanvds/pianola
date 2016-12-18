/*
  ==============================================================================

    MuteLookAndFeel.h
    Created: 27 Nov 2016 7:38:29pm
    Author:  yvan

  ==============================================================================
*/

#ifndef MUTELOOKANDFEEL_H_INCLUDED
#define MUTELOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

struct MuteLookAndFeel : public LookAndFeel_V3 {
public:
  MuteLookAndFeel();


  void drawRoundThumb(Graphics& g, const float x, const float y, const float diameter, 
    const Colour& colour, float outlineThickness);

  void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
    bool isMouseOverButton, bool isButtonDown) override;

  void drawTickBox(Graphics& g, Component& component,
    float x, float y, float w, float h,
    bool ticked,
    bool isEnabled,
    bool isMouseOverButton,
    bool isButtonDown) override;

  void drawToggleButton(Graphics &, ToggleButton &, bool isMouseOverbutton, bool isButtonDown) override;

  void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider) override;

  void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider) override;

  void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
    float /*sliderPos*/,
    float /*minSliderPos*/,
    float /*maxSliderPos*/,
    const Slider::SliderStyle /*style*/, Slider& slider) override;

  void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

private:
  ScopedPointer<Drawable> ledOff;
  ScopedPointer<Drawable> ledOn;
};




#endif  // MUTELOOKANDFEEL_H_INCLUDED
