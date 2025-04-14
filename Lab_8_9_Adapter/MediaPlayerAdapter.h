#pragma once

#include "NewMediaPlayer.h"
#include "OldMediaPlayer.h"
#include <string>


class MediaPlayerAdapter : public NewMediaPlayer
{
public:
	MediaPlayerAdapter(OldMediaPlayer* player)
		:oldPlayer(player)
	{}
	virtual ~MediaPlayerAdapter() = default;

	void play(const std::string& fileName) override
	{
		std::cout << "[MediaPlayerAdapter] received file: " << fileName << std::endl;

		std::string audioType;
		size_t pos = fileName.rfind('.');
		if (pos != std::string::npos)
		{
			std::string extension = fileName.substr(pos + 1);
			if (extension == "mp3" || extension == "wav")
				audioType = extension;
			else
			{
				std::cout << "[MediaPlayerAdapter] Type " << extension << " have been converted to mp3" << std::endl;
				audioType = "mp3";
			}
		}
		else
		{
			audioType = "unsupported";
		}

		std::cout << "[MediaPlayerAdapter] Converted audio type: " << audioType << std::endl;
		oldPlayer->play(audioType, fileName.substr(0, pos) + "." + audioType);
	}

private:
	OldMediaPlayer* oldPlayer = nullptr;
};