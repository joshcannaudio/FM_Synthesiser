/*
  ==============================================================================

    MyComponent.cpp
    Created: 13 Dec 2021 9:00:31pm
    Author:  Josh Cann

  ==============================================================================
*/

#include "MyComponent.h"

MyComponent::MyComponent(){}

MyComponent::~MyComponent(){}

void MyComponent::mouseEnter(const MouseEvent &event)
{
    onComponent = true;
    mouseUpdate();
}

void MyComponent::mouseExit(const MouseEvent &event)
{
    onComponent = false;
    mouseUpdate();
}

void MyComponent::mouseDown(const MouseEvent &event)
{
    buttonIsOn == true ? buttonIsOn = false : buttonIsOn = true;
    buttonDown = true;
    mouseUpdate();
}

void MyComponent::mouseUp(const MouseEvent &event)
{
    buttonDown = false;
    mouseUpdate();
}

const bool MyComponent::isOnComponent() { return onComponent; }

const bool MyComponent::buttonIsDown() { return buttonDown; }

const bool MyComponent::isButtonOn() { return buttonIsOn; }

void MyComponent::mouseUpdate(){}

