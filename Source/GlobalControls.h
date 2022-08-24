/*
  ==============================================================================

    GlobalControls.h
    Created: 13 Jan 2022 1:11:20am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyComponent.h"

struct MyButton : public MyComponent {
    /** Paints the Button */
    void paint(Graphics& g) override;
    
    /** Called when a mouse enters the component */
    void mouseUpdate() override;
    
    std::string labelText = "FM Off";
};

class GlobalControls : public Component {
public:
    /** Constructor */
    GlobalControls();
    
    /** Paints the controls */
    void paint(Graphics& g) override;
    
    Slider FMTone, masterVolume, filterCutoff;
private:
    Label label;
    Label volumeLabel, cutoffLabel, FMToneLabel;
    MyButton FMToggle;
};
