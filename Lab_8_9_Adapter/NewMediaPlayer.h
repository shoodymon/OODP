#pragma once


class NewMediaPlayer
{
public:
	virtual ~NewMediaPlayer() = default;

	virtual void play(const std::string& fileName)
	{
		std::cout << "NewMediaPlayer is playing with fileName: " << fileName << std::endl;
	}
};