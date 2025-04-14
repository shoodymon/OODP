#pragma once

#include "OldMediaPlayer.h"
#include "MediaPlayerAdapter.h"


class Client 
{
public:
    void run() 
    {
        OldMediaPlayer oldPlayer;

        MediaPlayerAdapter adapter(&oldPlayer);

        std::cout << "\n[Client] Testing support for .mp3" << std::endl;
        adapter.play("track.mp3");

        std::cout << "\n[Client] Testing support for .wav" << std::endl;
        adapter.play("sound.wav");

        std::cout << "\n[Client] Testing unsupported file type: .mp4" << std::endl;
        adapter.play("video.mp4");
    }
};