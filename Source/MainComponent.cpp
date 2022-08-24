#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent(Audio& a) : audio (a)
{
    setSize (750, 600);
    
    for(int i = 0; i < 4; i++)
        addAndMakeVisible(oscPanel[i]);
    
    addAndMakeVisible(globalControls);
    
    // Come back to this !!!
    addAndMakeVisible(effectsRack);
    
    for(int i = 0; i < 4; i++) {
        oscPanel[0].envelopeSlider[i].addListener(this);
        oscPanel[1].envelopeSlider[i].addListener(this);
        oscPanel[2].envelopeSlider[i].addListener(this);
        oscPanel[3].envelopeSlider[i].addListener(this);
    }
    
    for(int i = 0; i < 2; i++) {
        oscPanel[0].oscControls[i].addListener(this);
        oscPanel[1].oscControls[i].addListener(this);
        oscPanel[2].oscControls[i].addListener(this);
        oscPanel[3].oscControls[i].addListener(this);
    }
    
    for(int i = 0; i < 2; i++)
        effectsRack.effect[i].powerButton.addMouseListener(this, false);
    
    for(int i = 0; i < 2; i++) {
        effectsRack.effect[i].parameters[0].addListener(this);
        effectsRack.effect[i].parameters[1].addListener(this);
        effectsRack.effect[i].parameters[2].addListener(this);
    }
    
    globalControls.masterVolume.addListener(this);
    globalControls.FMTone.addListener(this);
    globalControls.filterCutoff.addListener(this);
    
    addAndMakeVisible(presetSelector);
    presetSelector.addListener(this);
    presetSelector.addItemList(presetNames, 1);
    presetSelector.setTextWhenNoChoicesAvailable("Choose Preset");
    presetSelector.setSelectedId(1);
    loadPreset(preset1);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::transparentBlack);
    
    // Oscillators
    for (int i = 0; i < 4; i++) {
        int yPos;
        i > 0 ? yPos = oscPanel[i - 1].getBottom() : yPos = 0;
        oscPanel[i].setBounds(0, yPos, getWidth() * 0.6, getHeight() * 0.25);
        oscPanel[i].setLabelText(labels[i]);
    }
    
    auto panelRight = oscPanel[0].getRight();
    
    // Global Controls
    globalControls.setBounds(panelRight, 0, getWidth() * 0.4, getHeight() * 0.25);
    
    // Effects Rack
    effectsRack.setBounds(panelRight, globalControls.getBottom(), getWidth() * 0.4, getHeight() * 0.5);
    
    g.setColour(Colours::black);
    g.fillRect(panelRight, effectsRack.getBottom(), getWidth() * 0.4, getHeight() * 0.05);
    g.setColour(Colours::white);
    g.drawText("Presets: ", panelRight, effectsRack.getBottom(), getWidth() * 0.3, getHeight() * 0.05, NotificationType::dontSendNotification);
    presetSelector.setBounds(panelRight * 1.15, effectsRack.getBottom(), getWidth() * 0.3, getHeight() * 0.05);
    
    // Envelope
//    envelope.setBounds(oscPanel[0].getRight(), effectsRack.getBottom(), getWidth() * 0.3, getHeight() * 0.25);
    
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

//MenuBarCallbacks==============================================================
StringArray MainComponent::getMenuBarNames()
{
    auto names = { "File" };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
    return menu;
}

void MainComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
    if (topLevelMenuIndex == FileMenu)
    {
        if (menuItemID == AudioPrefs)
        {
            DialogWindow::LaunchOptions la;
            la.dialogTitle = "Audio Settings";
            OptionalScopedPointer<Component> osp (std::make_unique<AudioDeviceSelectorComponent>
                                                  (audio.getAudioDeviceManager(),
                                                   1, 2, 2, 2,
                                                   true, true, true, false));
            osp->setSize (450, 350);
            la.content = std::move (osp);
            la.componentToCentreAround = this;
            la.launchAsync();
        }
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    // Osc Panels =============================================================
    for(int i = 0; i < 2; i++)
        Parameters::parameters[i] = oscPanel[0].oscControls[i].getValue();
    for(int i = 0; i < 4; i++)
        Parameters::parameters[i + 2] = oscPanel[0].envelopeSlider[i].getValue();
    
    for(int i = 0; i < 2; i++)
        Parameters::parameters[i + 6] = oscPanel[1].oscControls[i].getValue();
    for(int i = 0; i < 4; i++)
        Parameters::parameters[i + 8] = oscPanel[1].envelopeSlider[i].getValue();
    
    for(int i = 0; i < 2; i++)
        Parameters::parameters[i+12] = oscPanel[2].oscControls[i].getValue();
    for(int i = 0; i < 4; i++)
        Parameters::parameters[i+14] = oscPanel[2].envelopeSlider[i].getValue();
    
    for(int i = 0; i < 2; i++)
        Parameters::parameters[i+18] = oscPanel[3].oscControls[i].getValue();
    for(int i = 0; i < 4; i++)
        Parameters::parameters[i+20] = oscPanel[3].envelopeSlider[i].getValue();
    
    // Global Parameters =========================================================
    Parameters::parameters[24] = globalControls.FMTone.getValue();
    Parameters::parameters[25] = globalControls.filterCutoff.getValue();
    Parameters::parameters[26] = globalControls.masterVolume.getValue();
    
    //Effects Parameters ======================================================
    for(int i = 0; i < 3; i++)
        Parameters::parameters[i+28] = effectsRack.effect[0].parameters[i].getValue();
    for(int i = 0; i < 3; i++)
        Parameters::parameters[i+32] = effectsRack.effect[1].parameters[i].getValue();
}

void MainComponent::mouseDown(const MouseEvent & event)
{
    Parameters::parameters[27] = effectsRack.isEffectOn(0);
    Parameters::parameters[31] = effectsRack.isEffectOn(1);
    Parameters::parameters[35] = effectsRack.isEffectOn(2);
}

void MainComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{    
    if(presetSelector.getSelectedIdAsValue() == 1)
        loadPreset(preset1);
    if(presetSelector.getSelectedIdAsValue() == 2)
        loadPreset(preset2);
    if(presetSelector.getSelectedIdAsValue() == 3)
        loadPreset(preset3);
}

void MainComponent::loadPreset(std::array<float, 25> presetValues)
{
    for(int i = 0; i < 25; i++) {
        Parameters::parameters[i] = presetValues[i];
    }
    
    for(int i = 0; i < 2; i++)
        oscPanel[0].oscControls[i].setValue(presetValues[i], NotificationType::sendNotificationSync);
    for(int i = 0; i < 4; i++)
        oscPanel[0].envelopeSlider[i].setValue(presetValues[i+2], NotificationType::sendNotificationSync);
    for(int i = 0; i < 2; i++)
        oscPanel[1].oscControls[i].setValue(presetValues[i + 6], NotificationType::sendNotificationSync);
    for(int i = 0; i < 4; i++)
        oscPanel[1].envelopeSlider[i].setValue(presetValues[i + 8], NotificationType::sendNotificationSync);
    for(int i = 0; i < 2; i++)
        oscPanel[2].oscControls[i].setValue(presetValues[i + 12], NotificationType::sendNotificationSync);
    for(int i = 0; i < 4; i++)
        oscPanel[2].envelopeSlider[i].setValue(presetValues[i + 14], NotificationType::sendNotificationSync);
    for(int i = 0; i < 2; i++)
        oscPanel[3].oscControls[i].setValue(presetValues[i + 18], NotificationType::sendNotificationSync);
    for(int i = 0; i < 4; i++)
        oscPanel[3].envelopeSlider[i].setValue(presetValues[i + 20], NotificationType::sendNotificationSync);

    globalControls.FMTone.setValue(presetValues[24]);
}

