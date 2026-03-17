#pragma once

#include <iostream>
#include<string>
#include<deque>

#include "audio.h";

void addToQueue(std::string path);
void skipCurrent();
void previousSound();
std::string getCurrentSongPath();