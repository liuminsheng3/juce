/*
  ==============================================================================

    PlayListComponent.h
    Created: 21 Feb 2022 8:26:57am
    Author:  Sheng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FileHandler.h"

//==============================================================================
/*
*/
class PlayListComponent  :  public juce::Component,
                            public AudioSource,
                            public TableListBoxModel,
                            public FileDragAndDropTarget
{
public:
    //==============================================================================
    PlayListComponent(AudioFormatManager & _formatManager);
    
    ~PlayListComponent() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //==============================================================================
    int getNumRows() override;
    
    void paintRowBackground(Graphics    &,
                            int         rowNumber,
                            int         width,
                            int         height,
                            bool        rowIsSelected
                            ) override;
    
    void paintCell(Graphics &,
                   int      rowNumber,
                   int      columnId,
                   int      width,
                   int      height,
                   bool     rowIsSelected
                   ) override;
    
    //==============================================================================
    bool isInterestedInFileDrag (const StringArray &files) override;
    
    void filesDropped (const    StringArray &files,
                       int      x,
                       int      y
                       ) override;
    
    //==============================================================================
    void prepareToPlay (int     samplesPerBlockExpected,
                        double  sampleRate
                        ) override;
    
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
    //==============================================================================
    
    void addFileToList(URL fileURL);
    
    std::string pathParser(std::string path);
    
    std::string secondsToString(int totalSeconds);
    
private:
    
    //==============================================================================
    std::vector<std::string> traceNames;
    TableListBox tableListBox;
    AudioFormatManager & formatManager;
    std::vector<std::vector<std::string>> audioData;
    FileHandler fileHandler{FileHandler::getFilePath()};
    Array<var>* recordsArray; 
    int counter = 0;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayListComponent)
};
