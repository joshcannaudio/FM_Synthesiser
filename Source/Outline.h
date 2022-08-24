/*
  ==============================================================================

    Outline.h
    Created: 15 Dec 2021 2:22:25am
    Author:  Josh Cann

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyComponent.h"

class Outline : public MyComponent {
public:
    void paint(Graphics& g) override;
};
