
//This implementation file contains all the audio/miniaudio related code.
// for now i have used high level api's planned to futher use low level api for equilizers

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include "audio.h"
using namespace std;

float soundLength = 0.0f;
float cursor = 0.0f;
string currentTitle = ""; //song Title
bool playingStatus = false;


void check_Result(ma_result result, const string& error_message) { // A simple error handling implementation can be used with MA methods returning MA_SUCCESS.
	if (result != MA_SUCCESS) {
		throw runtime_error(error_message + "(code: " + to_string(result) + ")");
	}
}

ma_engine engine; //audio engine 
ma_result result; //result variable
ma_sound sound; //sound data

ma_engine* getEngine() { //returns engine pointer
	return &engine;
}

ma_sound* getSound() { // returns sound pointer
	return &sound;
}

void uninitAll() { // uninitialize all pointers
	ma_sound_uninit(&sound);
	playingStatus = false;
	ma_engine_uninit(&engine);
}

void initEngine() {
	check_Result(ma_engine_init(NULL, &engine), "Engine Cannot be initiated");
}

void init_sound_from_file(string path) { // initialize the sound data with the music path given
	if (path == "selection cancelled") {

		return;
	}
	currentTitle = "Unkown Title";
	ma_sound_uninit(&sound);
	check_Result(ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &sound), "Sound could not be initialized"); // MA_SOUND_FLAG_STREAM used to load the song in chunks
	playingStatus = true;
	ma_sound_get_length_in_seconds(&sound, &soundLength);
	ma_sound_set_volume(&sound, 0.5f);
	ma_sound_start(&sound);
}

float getLength() {
	return soundLength;
}

float getProg() { //returns Cursor at current position

	check_Result(ma_sound_get_cursor_in_seconds(&sound, &cursor), "No progress here gng!!");
	return cursor;
}

void setSeek(float time) { //seeks song to given float time
	check_Result(ma_sound_seek_to_second(&sound, time), "cannot seek there mate!");
}

vector<string> getTitle(std::string path) {
	std::string title = "Unknown", artist = "Unknown Artist";
	TagLib::FileRef track(path.c_str()); // sets track meta-data to the track obj
	if (!track.isNull() && track.tag()) {
		TagLib::String tagTitle = track.tag()->title(), tagArtist = track.tag()->artist();
		if (!tagTitle.isEmpty()) {
			const char* titlePtr = tagTitle.toCString(true);
			const char* artistPtr = tagArtist.toCString(true);
			if (titlePtr != nullptr && artistPtr != nullptr) {
				title = string(titlePtr);
				artist = string(artistPtr);
			}
		}

	}
	return { title, artist };
}


bool checkPlaying() { //returns songs playing status
	return (playingStatus == true) ? true : false;
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
