/*
  ==============================================================================

    PanelBar.h
    Created: 15 Dec 2021 1:26:07am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyComponent.h"

class PanelBar : public MyComponent {
public:
    PanelBar();
    
    void paint(Graphics& g) override;
    
    void panelHasLabel(bool hasLabel);
    
    Label oscName;
    
private:
    std::string labelName = "Osc";
    bool hasLabel_ = false;
};
