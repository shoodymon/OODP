#pragma once

#include <iostream>
#include <string>



class OldMediaPlayer 
{
public:
    virtual ~OldMediaPlayer() = default;

    void play(const std::string& audioType, const std::string& fileName) 
    {
        if (audioType == "mp3" || audioType == "wav") 
        {
            std::cout << "[OldMediaPlayer] Playing " << audioType << " file: " << fileName << std::endl;
        }
        else 
        {
            std::cerr << "[OldMediaPlayer] Error: Unsupported audio type " << audioType << "' for file: " << fileName << std::endl;
        }
    }

};
