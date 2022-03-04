#pragma once

#include <JuceHeader.h>
#include "AudioPlayer.h"
#include "DeckGUI.h"
#include "PlayListComponent.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent


{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    


    
private:
    //==============================================================================
    
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbnailCache{100};
    
    AudioPlayer audioPlayerOne{formatManager};
    
    PlayListComponent playList{ formatManager };
    
    DeckGUI deckOne{&audioPlayerOne,
                    formatManager,
                    thumbnailCache};
    
    AudioPlayer audioPlayerTwo{formatManager};
    
    DeckGUI deckTwo{&audioPlayerTwo,
                    formatManager,
                    thumbnailCache};
    
    MixerAudioSource mixerSource;
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
