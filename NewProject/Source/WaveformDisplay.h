/*
  ==============================================================================

    WaveformDisplay.h
    Created: 19 Feb 2022 4:43:18pm
    Author:  Sheng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager & formatManager,
                    AudioThumbnailCache & thumbnailCache);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void loadAudioFileByURL(URL audioURL);

    void changeListenerCallback (ChangeBroadcaster *source) override;
    void setPositionRelative(double pos);

    
private:
    bool isLoaded;
    bool isFollowingTransport;
    double relativePosition;
    AudioThumbnail audioThumb;
    DrawableRectangle currentPositionMarker;
    

    void updateCursorPosition();
    
    bool canMoveTransport() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
