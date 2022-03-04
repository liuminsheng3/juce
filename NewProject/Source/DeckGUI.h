/*
  ==============================================================================

    DeckGUI.h
    Created: 19 Feb 2022 1:50:42pm
    Author:  Sheng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioPlayer.h"
#include "WaveformDisplay.h"
#include "FileHandler.h"

//==============================================================================
/*
*/
class DeckGUI  :    public juce::Component,
                    public TextButton::Listener,
                    public Slider::Listener,
//                    public FileDragAndDropTarget,
                    public Timer
{
public:
    DeckGUI(AudioPlayer * _player,
            AudioFormatManager & formatManager,
            AudioThumbnailCache & thumbnailCache);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    
    void buttonClicked(Button * button) override;
    
    void sliderValueChanged (Slider *slider) override;
    
    // file drag pure virtual function
//    bool isInterestedInFileDrag (const StringArray &files) override;
//    void filesDropped (const StringArray &files, int x, int y) override;
    
    void timerCallback() override;

private:
    bool isLoaded;
    bool isPlaying;
    
    TextButton playAndStopButton{"PLAY"};
    TextButton loadButton{"LOAD"};
    Time time;
    Slider speedSlider{"SPEED"};
    Slider volumeSlider{"VOLUME"};
    Slider posSlider{"POSITION"};
    
    FileHandler fileHandler;
    
    AudioPlayer * player;
    
    WaveformDisplay waveformDisplay;

    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
