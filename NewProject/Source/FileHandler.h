/*
  ==============================================================================

    FileHandler.h
    Created: 21 Feb 2022 9:20:41pm
    Author:  Sheng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FileHandler{
public:
    FileHandler(std::string path);
    ~FileHandler();
    std::string static getFilePath();
    void setupFile();
    void writeFile(DynamicObject* objData);
    Array<var>* loadFile();
    
private:
    var data;
    File file{"./audio_file_data/file_path.json"};
};
