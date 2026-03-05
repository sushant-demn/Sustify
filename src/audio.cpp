// MusicStreamingApp.cpp : Defines the entry point for the application.
//
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

//#define TAGLIB_STATIC
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "audio.h"
using namespace std;

float soundLength = 0.0f;
float cursor = 0.0f;
string currentTitle = "";


void check_Result(ma_result result, const string& error_message) {
	if (result != MA_SUCCESS) {
		throw runtime_error(error_message + "(code: " + to_string(result) + ")");
	}
}

ma_engine engine; //audio engine
ma_result result; //result variable
ma_sound sound; //sound data

ma_engine* getEngine() {
	return &engine;
}

ma_sound* getSound() {
	return &sound;
}

void uninitAll() {
	ma_sound_uninit(&sound);
	ma_engine_uninit(&engine);
}

void initEngine() {
	check_Result(ma_engine_init(NULL, &engine), "Engine Cannot be initiated");
}

void init_sound_from_file(string path) { // initialize the sound data with the music path given
	if (path == "selection cancelled") {
		
		return;		
	}
	ma_sound_uninit(&sound);
	check_Result(ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &sound), "Sound could not be initialized"); // MA_SOUND_FLAG_STREAM used to load the song in chunks
	ma_sound_get_length_in_seconds(&sound, &soundLength);
	ma_sound_set_volume(&sound, 0.5f);
	{
		TagLib::FileRef track(path.c_str()); // sets track meta-data to the track obj
		if (!track.isNull() && track.tag()) {
			TagLib::String tagTitle = track.tag()->title();
			if (!tagTitle.isEmpty()) {
				const char* titlePtr = tagTitle.toCString(true);
				if (titlePtr != nullptr) {
					currentTitle = string(titlePtr);
				}
			}

		}
	}
}

float getLength() {
	return soundLength;
}

float getProg() {

	check_Result(ma_sound_get_cursor_in_seconds(&sound, &cursor), "No progress here gng!!");
	return cursor;
}

void setSeek(float time) {
	check_Result(ma_sound_seek_to_second(&sound, time), "cannot seek there mate!");
}

string getTitle() {
	return currentTitle;
}

/*int main() //for debuging shit
{
	initEngine();
	cout << "engine initialized\n";

	string path = getPath(); //path to the music file

	init_sound_from_file(path);

	cout << "sound initialized\n";

	ma_sound_start(&sound);
	cin.get();
	ma_sound_uninit(&sound);
	ma_engine_uninit(&engine);
	return 0;
}*/
