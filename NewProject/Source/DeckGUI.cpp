/*
  ==============================================================================

    DeckGUI.cpp
    Created: 19 Feb 2022 1:50:42pm
    Author:  Sheng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(AudioPlayer * _player,
                 AudioFormatManager & formatManager,
                 AudioThumbnailCache & thumbnailCache
                 ) :
                     isLoaded(false),
                     isPlaying(false),
                     player(_player),
                     fileHandler(FileHandler::getFilePath()),
                     waveformDisplay(formatManager,thumbnailCache)
{
    addAndMakeVisible(playAndStopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playAndStopButton.addListener(this);
    loadButton.addListener(this);
    
    speedSlider.addListener(this);
    volumeSlider.addListener(this);
    posSlider.addListener(this);
    
    volumeSlider.setRange(0.0f, 1.0f);
    speedSlider.setRange(0.0f, 3.0f);
    posSlider.setRange(0.0f, 1.0f);
    
    volumeSlider.setValue(0.5f);
    speedSlider.setValue(1.0f);
    posSlider.setValue(0.0f);
    
    startTimer(50);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);

}

void DeckGUI::resized()
{
    double interval = getWidth()/10;
    
    playAndStopButton.setBounds(0, interval * 1, getWidth(), interval);

    volumeSlider.setBounds(0, interval * 2, getWidth(), interval);
    speedSlider.setBounds(0, interval * 3, getWidth(), interval);
    posSlider.setBounds(0, interval * 4, getWidth(), interval);
    
    loadButton.setBounds(0, interval * 5, getWidth(), interval);
    
    waveformDisplay.setBounds(0, interval * 6, getWidth(), interval * 4);

}

void DeckGUI::buttonClicked(Button * button){
    if (button == &playAndStopButton){
        
        if(button->getButtonText() == "PLAY"){
            button->setButtonText("STOP");
            player->play();

        }
        else if(button->getButtonText() == "STOP"){
            button->setButtonText("PLAY");
            player->stop();
        }
    }
    if(button == &loadButton){
/**---------------------------------------------------------------------------*/
/**FileHandler class test, should be deleted after testing*/

//        std::cout<<FileHandler::getFilePath()<<std::endl;
//        //test writeFile function
//        DynamicObject* obj = new DynamicObject{};
//        Identifier name {"song Name"};
//        Identifier path {"path"};
//        var songName {"song 1"};
//        var pathName {"~/home"};
//        obj->setProperty(name, songName);
//        obj->setProperty(path, pathName);
//        
//        fileHandler.writeFile(obj);
//        var obj = fileHandler.loadFile();
//        std::cout<<"DeckGUI::buttonClicked, obj size = "obj.size()<<std::endl;
        
/**---------------------------------------------------------------------------*/
        if(player->isPlaying()){
            playAndStopButton.setButtonText("PLAY");
            player->stop();
            
        }
        FileChooser chooser("choose an audio file to play...");
        if(chooser.browseForFileToOpen()){
            player->loadAudioFileByURL(URL{chooser.getResult()});
            waveformDisplay.loadAudioFileByURL(URL{chooser.getResult()});
            isLoaded = true;
        }
    }
}

void DeckGUI::sliderValueChanged (Slider *slider) {
    if(slider == &volumeSlider){
        std::cout<<"volume slider : "<<slider->getValue()<<std::endl;
        player->setGain(slider->getValue());
    }
    if(slider == &speedSlider){
        //make sure resampling ratio won't be smaller than 0.
        if(slider->getValue() != 0.0f)
            player->setSpeed(slider->getValue());
    }
    if(slider == &posSlider){
        player->setPositionRelative(slider->getValue());

    }
}



//bool DeckGUI::isInterestedInFileDrag (const StringArray &files){
//    std::cout<<"DeckGUI::isInterestedInFileDrag"<<std::endl;
//    return true;
//}

//void DeckGUI::filesDropped (const StringArray &files, int x, int y){
//    std::cout<<"DeckGUI::filesDropped"<<std::endl;
//    for(String filename : files){
//        std::cout<<filename<<std::endl;
//    }
//    if(files.size() == 1){
//        player->loadAudioFileByURL(URL{File(files[0])});
//        waveformDisplay.loadAudioFileByURL(URL{File(files[0])});
//    }
//
//}

void DeckGUI::timerCallback()
{

    if(isLoaded)
        waveformDisplay.setPositionRelative(player->getPositionRelative());
    repaint();
}
