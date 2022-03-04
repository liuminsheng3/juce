/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 19 Feb 2022 4:43:18pm
    Author:  Sheng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManager,
                                 AudioThumbnailCache & thumbnailCache)
                                :isLoaded(false),
                                 isFollowingTransport(false),
                                 relativePosition(0.0f),
                                 audioThumb(512, formatManager, thumbnailCache)

{
    audioThumb.addChangeListener(this);
    
    currentPositionMarker.setFill (Colours::white.withAlpha (0.85f));
    addAndMakeVisible (currentPositionMarker);

}

WaveformDisplay::~WaveformDisplay()
{
    audioThumb.removeChangeListener(this);
    
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    if(isLoaded){
        
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
        g.setColour(Colours::lightgreen);
        g.drawLine(relativePosition * getWidth(),
                   0,
                   relativePosition * getWidth(),
                   getHeight()
                   );
    }
    else{
        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("File is not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
        
    }

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
void WaveformDisplay::loadAudioFileByURL(URL audioURL){

    audioThumb.clear();
    isLoaded = audioThumb.setSource(new URLInputSource(audioURL));
   
    if(isLoaded){
        std::cout<<"WaveformDisplay::loadAudioFileByURL---Loaded"<<std::endl;
    }
    else{
        std::cout<<"WaveformDisplay::loadAudioFileByURL---Not Loaded"<<std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source){
    if(isLoaded){
        repaint();
    }
        
}

bool WaveformDisplay::canMoveTransport() const noexcept
{
    
    return (!isFollowingTransport && isLoaded);
}

//void WaveformDisplay::timerCallback(){
//    if(canMoveTransport()){
//        updateCursorPosition();
//    }
//}

void WaveformDisplay::updateCursorPosition()
{
//    currentPositionMarker.setVisible (transportSource.isPlaying() || isMouseButtonDown());
//
//    currentPositionMarker.setRectangle (Rectangle<float> (timeToX (transportSource.getCurrentPosition()) - 0.75f, 0,
//                                                          1.5f, (float) (getHeight() - scrollbar.getHeight())));
}

void WaveformDisplay::setPositionRelative(double pos)
{
    relativePosition = pos;
}
