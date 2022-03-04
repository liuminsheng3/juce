/*
  ==============================================================================

    PlayListComponent.cpp
    Created: 21 Feb 2022 8:26:57am
    Author:  Sheng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayListComponent.h"

//==============================================================================
PlayListComponent::PlayListComponent(AudioFormatManager & _formatManager)
    : formatManager(_formatManager),
      recordsArray(nullptr)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(tableListBox);
    tableListBox.getHeader().addColumn("Track title", 1, 500);
    tableListBox.getHeader().addColumn("Length", 2, 500);
    traceNames.push_back("song 1");
    traceNames.push_back("song 2");
    traceNames.push_back("song 3");
    traceNames.push_back("song 4");
    traceNames.push_back("song 5");
    traceNames.push_back("song 6");
    traceNames.push_back("song 7");
    traceNames.push_back("song 8");
    traceNames.push_back("song 9");
    
    fileHandler.setupFile();
//    var temp = fileHandler.loadFile();
//    std::cout<<"PLC::Constructor, is data an Array: "<<(temp.isArray()?"True":"False")<<std::endl;
    recordsArray =  fileHandler.loadFile();
    std::cout<<"records array size is = "<<recordsArray->size()<<std::endl;
    

    tableListBox.setModel(this);
}

PlayListComponent::~PlayListComponent()
{
}

void PlayListComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlayListComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayListComponent::resized()
{
    tableListBox.setBounds(0, 0, getWidth(), getHeight());

}

int PlayListComponent::getNumRows()
{
    std::cout<<"PLC::getNumRows, records size = "<<recordsArray->size()<<std::endl;
    return recordsArray->size();
}
void PlayListComponent::paintRowBackground(
                        Graphics    & g,
                        int         rowNumber,
                        int         width,
                        int         height,
                        bool        rowIsSelected
                        )
{
    if(rowIsSelected){
        g.fillAll(Colours::orange);
    }
    else{
        g.fillAll(Colours::grey);
    }
}

void PlayListComponent::paintCell(Graphics & g,
               int      rowNumber,
               int      columnId,
               int      width,
               int      height,
               bool     rowIsSelected
               )
{
    if(recordsArray == nullptr)
    {
        std::cout<<"PlayListComponent::paintCell:: recordsArray null ptr"<<std::endl;
        return;
    }
    std::cout<<"PLC::paintCell:: success"<<std::endl;
    var temp_first = (*recordsArray)[rowNumber];
     

    //4. get DynamicObject * from var --> DynamicObject
    DynamicObject * obj = temp_first.getDynamicObject();
    
    //5. get property of obj --> var
    std::cout<<"PLC: paintCell =  has property song name"<<std::endl;
    std::cout<<obj->hasProperty("song Name")<<std::endl;
    if(obj->hasProperty("song Name"))
    {
        var name = obj->getProperty("song Name");
        std::cout<<name.toString()<<std::endl;
        if(columnId == 1)
        {

            g.drawText(name.toString(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredLeft,
                       true);
        }
    }
    
    if(obj->hasProperty("path"))
    {
        var path = obj->getProperty("path");
        
        if(columnId == 2)
        {

            g.drawText(path.toString(),
                       2,
                       0,
                       width - 4,
                       height,
                       Justification::centredLeft,
                       true);
        }
    }

    
  


}

bool PlayListComponent::isInterestedInFileDrag (const StringArray &files)
{
    return true;
}
void PlayListComponent::filesDropped (const StringArray &files, int x, int y)
{
    //1. we need someData structure store file path, audio file name, audio length
    //2. we need some Data to find audio file name
    //3. we need to write data into columns.
    for(String filePath : files)
    {
        
        auto reader = formatManager.createReaderFor(File(filePath.toStdString()));
        
        if(reader != nullptr)
        {
            int totalLengthInSec = reader->lengthInSamples / reader->sampleRate;
            
            std::string timeString = secondsToString(totalLengthInSec);
            
            std::string fileName = pathParser(filePath.toStdString());
            
            
            std::cout<<"PlayList: length = "<<timeString<<", file name = "<<fileName<<std::endl;
        }

        
    }
}

void PlayListComponent::addFileToList(URL fileURL)
{
    
}
/*  path: file path, standard c++ string.
    parser: used to parse the file path, c++ char.
    position: on which parser  that want to parse the file. -1 mean the last one, 0 means the first one.
    
 */
std::string PlayListComponent::pathParser(std::string path)
{
    #if JUCE_IOS
        #define PARSER char parser = '\';
    #else
        #define PARSER char parser = '/';
    #endif
    
    PARSER
    
    std::string result="";
    std::size_t start = path.find_last_of(parser);
    result = path.substr((start+1));
    return result;
}


void PlayListComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}
void PlayListComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    
}
void PlayListComponent::releaseResources()
{
    
}

std::string PlayListComponent::secondsToString(int totalSeconds)
{
    std::string timeString = "";
    
    if(totalSeconds <=0)
    {
        return timeString;
    }
    
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    
    if(minutes < 10)
    {
        timeString += "0";
    }
    
    timeString += std::to_string(minutes);
    
    timeString += ":";
    
    if(seconds < 10)
    {
        timeString += "0";
    }
    timeString += std::to_string(seconds);
    
    return timeString;
}


