/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 19 Feb 2022 1:15:05am
    Author:  Sheng

  ==============================================================================
*/

#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(AudioFormatManager& _formatManager): formatManager(_formatManager){

}
AudioPlayer::~AudioPlayer(){

}

void AudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    
}
void AudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill){
    resampleSource.getNextAudioBlock(bufferToFill);
}
void AudioPlayer::releaseResources(){
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void AudioPlayer::loadAudioFileByURL(URL audioURL){

    auto * reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    
    
    if(reader != nullptr){
        std::cout<<reader->metadataValues.getAllKeys().size()<<std::endl;
        for (String key : reader->metadataValues.getAllKeys()) {
            DBG ("Key: " + key + " value: " + reader->metadataValues.getValue (key, "unknown"));
        }
      
        std::unique_ptr<AudioFormatReaderSource> newSource{new AudioFormatReaderSource{reader, true}};
        
        transportSource.setSource(newSource.get(),
                                  0,
                                  nullptr,
                                  reader->sampleRate,
                                  2);
        
        readerSource.reset(newSource.release());
    }
    else{
        std::cout<<"audio file can not be loaded"<<std::endl;
    }

}

void AudioPlayer::play(){
    transportSource.start();
}

void AudioPlayer::stop(){
    transportSource.stop();
    
}
void AudioPlayer::setGain(double gain){
    transportSource.setGain(gain);
    
}
void AudioPlayer::setSpeed(double samplesInPerOutputSample){
    resampleSource.setResamplingRatio(samplesInPerOutputSample);
}
void AudioPlayer::setPosition(double posInSecs){
    transportSource.setPosition(posInSecs);
}

void AudioPlayer::setPositionRelative(double pos){
    double posInSecs = pos * transportSource.getLengthInSeconds();
    setPosition(posInSecs);
}

double AudioPlayer::getCurrentPosition()
{
    return transportSource.getCurrentPosition();
}
double AudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
bool AudioPlayer::isPlaying()
{
    return transportSource.isPlaying();
}
