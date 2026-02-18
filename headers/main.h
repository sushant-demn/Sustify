#pragma once
#include <iostream>
#include "portable-file-dialogs.h"
#include<string>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "file_system.h"

ma_result init_sound_from_file(std::string path);