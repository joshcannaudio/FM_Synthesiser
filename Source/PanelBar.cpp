/*
  ==============================================================================

    PanelBar.cpp
    Created: 15 Dec 2021 1:26:07am
    Author:  Josh Cann

  ==============================================================================
*/

#include "PanelBar.h"

PanelBar::PanelBar()
{
    addAndMakeVisible(oscName);
}

void PanelBar::paint(Graphics& g)
{
    // Panel Bar
    g.setColour(Colours::black);
    g.fillRect(0, 0, getWidth(), getHeight());
    
    // Label
    if(hasLabel_) {
        oscName.setBounds(getWidth() / 5, getHeight() / 3, getWidth(), getHeight() / 2);
    }
}

void PanelBar::panelHasLabel(bool hasLabel)
{
    hasLabel_ = hasLabel;
}
