#pragma once

#include <JuceHeader.h>
#include "Audio.h"
#include "Parameters.h"
#include "OscillatorComponent.h"
#include "GlobalControls.h"
#include "EffectsRack.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public Component,
                       public MenuBarModel,
                       public Slider::Listener,
                       public ComboBox::Listener
{
public:
    //==============================================================================
    MainComponent(Audio& a);
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //MenuBarEnums/MenuBarModel=====================================================
    enum Menus
    {
        FileMenu = 0,
        
        NumMenus
    };
    
    enum FileMenuItems
    {
        AudioPrefs = 1,
        
        NumFileItems
    };
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    // Sliders
    void sliderValueChanged(Slider* slider) override;
    
    // Mouse Listener
    void mouseDown(const MouseEvent & event) override;

    //
    void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;
    
    void loadPreset(std::array<float, 25> presetValues);
    
private:
    //==============================================================================
    // Your private member variables go here...
    Audio& audio;
//    SynthProcessor synthProcessor;
    
    OscillatorComponent oscPanel[4];
    GlobalControls globalControls;
    EffectsRack effectsRack;
    ComboBox presetSelector;
    StringArray presetNames = { "E-Piano", "Plucky FM", "Synth Piano" };
    
    std::string labels[4] = { "Osc A - FM Carrier", "Osc B - FM Modulator", "Osc C - FM Modulator", "Osc D - FM Modulator"};
    
    // E-Piano                          T    L    A    D    S     R
    std::array<float, 25> preset1 = {   0,    -3,   0.005,  2.7, -49,  0.3,   // Osc A
                                      -12,   -19,   0,  2.7, -52,  0.1,   // Osc B
                                       12,   -22,   0,  0.2, -40, 0.05,   // Osc C
                                        7,    -7, 0.7,  0.3, -60,  0.01,  24 }; // Osc D
    // Plucky FM
    std::array<float, 25> preset2 = { -12,    -2,   0,  0.3, -6,  1.4,   // Osc A
                                        0,   -24, 0,  0.25, -18,  0.09,   // Osc B
                                      -12,   -8,  0,  0.4, 0.0, 0.03,   // Osc C
                                        0,   -32,   0,  0.2, -60,  0.02,  40 }; // Osc D
    //
    std::array<float, 25> preset3 = {     0,    -6,   0,  2.7, -49,  0.3,   // Osc A
                                          0,   -20,   0,  2.7, -52,  0.1,   // Osc B
                                          0,   -32,   0,  0.2, -40, 0.05,   // Osc C
                                          12,   -9, 0.7,  0.3, -60,  0.01, 66 }; // Osc D

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
