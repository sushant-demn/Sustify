#pragma once

#include <iostream>
#include<string>
#include<deque>

#include "audio.h";

struct track
{
	std::string path;
	std::string title;
	std::string artist;

	//float duration;

};

void addToQueue(std::string path);
void skipCurrent();
void previousSound();
std::string getCurrentSongPath();
std::string getCurrentSongTitle();
std::string getQueue();
std::string getLatestMeta();
std::string getCurrentMeta();
void changeSong(int cursor);	