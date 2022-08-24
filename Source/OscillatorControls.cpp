/*
  ==============================================================================

    OscillatorControls.cpp
    Created: 15 Dec 2021 10:15:50am
    Author:  Josh Cann

  ==============================================================================
*/

#include "OscillatorControls.h"

OscillatorControls::OscillatorControls()
{
    addAndMakeVisible(oscControl);
    oscControl.setValue(0.7);
    oscControl.setRange(0, 1);
}

void OscillatorControls::paint(Graphics& g)
{
    oscControl.setSliderStyle(Slider::RotaryVerticalDrag);
    oscControl.setBounds(0, 0, getWidth(), getHeight());
    oscControl.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    // Visulises where the component is
//    g.setColour(Colours::whitesmoke);
//    g.drawRect(0, 0, getWidth(), getHeight());
}
