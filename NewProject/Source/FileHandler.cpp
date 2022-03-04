/*
  ==============================================================================

    FileHandler.cpp
    Created: 21 Feb 2022 9:20:41pm
    Author:  Sheng

  ==============================================================================
*/

#include "FileHandler.h"

/**
 1. open file
    a. if there's no directory, create one
    b. if there's no file, create one
    c. then open the file
 2. read file
    file.loadFileAsString()
 3. wrtie file
    file.replaceWithText()
 4.
 5. data type that store the it.
 6. 
 */

/**
 1. open file
 a. if there's no directory, create one
 b. if there's no file, create one
 c. then open the file*/

FileHandler::FileHandler(std::string path) :file(path)
{
/**------------------------------------------------------------------------------------------*/

}
FileHandler::~FileHandler()
{
    
}
void getPath()
{
   
}

std::string FileHandler::getFilePath()
{
    // find the excutable path, that's the closest file path of current working directory I can get.
    //excutablePath=
    //Users/imacpro/UOL/semester_3/oop/Otodecks/NewProject/Builds/MacOSX...
    std::string excutablePath = File::getSpecialLocation(
                       File::SpecialLocationType::
                       currentExecutableFile).getFullPathName().toStdString();
    
    //position of "Builds"
    std::size_t end = excutablePath.find("Builds");
    
    //get from beginning to "Builds"
    std::string playListFilePath = excutablePath.substr(0,end);
    
    playListFilePath += "Source/data/playListData.json";
    
    return playListFilePath;
}

void FileHandler::setupFile()
{
    if(!file.existsAsFile())
    {
        auto reuslt = file.create();
        
        std::cout<<"file did not exist, creating new one."<<std::endl;
    }
}

/**
 //1. parse from file --> var
 var parsedData = JSON::parse(file);
 
 //2. get Array from var--> Array<var> *
 Array<var>* array = parsedData.getArray();
 
 //3. get each var element(for loop) --> var
 for(int i = 0; i < array->size(); i++){
     var temp_first = (*array)[i];
      
     //4. get DynamicObject * from var --> DynamicObject
     DynamicObject * obj = temp_first.getDynamicObject();
     
     //5. get property of obj --> var
     var name = obj->getProperty("song Name");
     
     std::cout<<name.toString()<<std::endl;
     
     var path = obj->getProperty("path");
     
     std::cout<<path.toString()<<std::endl;
 */

Array<var>* FileHandler::loadFile()
{
    data = JSON::parse(file);
    
    std::cout<<"FHandler::loadFile, is data an Array: "<<(data.isArray()?"True":"False")<<std::endl;
    

    
    return data.getArray();
}

void FileHandler::writeFile(DynamicObject* objData)
{
    var data{objData};
    FileOutputStream  outputStream{file};
    
    JSON::writeToStream(outputStream, data);
}
