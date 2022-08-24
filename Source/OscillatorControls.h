/*
  ==============================================================================

    OscillatorControls.h
    Created: 15 Dec 2021 10:15:50am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyComponent.h"

class OscillatorControls : public MyComponent {
public:
    /** Constrcutor */
    OscillatorControls();
    
    void paint(Graphics& g) override;
    
    Slider oscControl;
    
private:
};
