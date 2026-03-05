#pragma once
#include <iostream>
#include<string>
#include "portable-file-dialogs.h"
#include "miniaudio.h"
#include "file_system.h"

ma_sound* getSound();
ma_engine* getEngine();
void uninitAll();
void initEngine();
void init_sound_from_file(std::string path);
float getLength();
float getProg();
void setSeek(float time);
std::string getTitle();