#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1000, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(deckOne);
    addAndMakeVisible(deckTwo);
    addAndMakeVisible(playList);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
//    shutdownAudio();
    
    
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    formatManager.registerBasicFormats();
    
    audioPlayerOne.prepareToPlay(samplesPerBlockExpected, sampleRate);
    audioPlayerTwo.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.addInputSource(&audioPlayerOne, false);
    mixerSource.addInputSource(&audioPlayerTwo, false);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    audioPlayerOne.releaseResources();
    audioPlayerTwo.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    deckOne.setBounds(0, 0, getWidth()/2, getHeight()/2);
    deckTwo.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()/2);
    playList.setBounds(0, getHeight()/2, getWidth(), getHeight()/2);
}




