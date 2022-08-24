/*
  ==============================================================================

    Outline.cpp
    Created: 15 Dec 2021 2:22:25am
    Author:  Josh Cann

  ==============================================================================
*/

#include "Outline.h"

void Outline::paint(Graphics& g)
{
     g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 5, 5);
}
