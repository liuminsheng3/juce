/*
  ==============================================================================

    AudioPlayer.h
    Created: 19 Feb 2022 1:15:05am
    Author:  Sheng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioPlayer : public AudioSource
{
        
public:
    AudioPlayer(AudioFormatManager& _formatManager);
    ~AudioPlayer();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void loadAudioFileByURL(URL audioURL);
    
    void play();
    void stop();
    void setGain(double gain);
    void setSpeed(double samplesInPerOutputSample);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    double getCurrentPosition();
    double getPositionRelative();
    bool isPlaying();
    
private:
    
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, true};
    
    
};




