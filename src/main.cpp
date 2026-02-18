// MusicStreamingApp.cpp : Defines the entry point for the application.
//

#include "main.h"
using namespace std;

ma_engine engine; //audio engine
ma_result result; //result variable
ma_sound sound; //sound data

ma_result init_sound_from_file(string path) { // initialize the sound data with the music path given

	return ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &sound); // MA_SOUND_FLAG_STREAM used to load the song in chunks
}

int main()
{
	result = ma_engine_init(NULL, &engine); // initialize the audio engine
	if (result != MA_SUCCESS) {
		cout << "engine didn't initialized\n";
		return 0;
	}
	cout << "engine initialized\n";

	string path = getPath(); //path to the music file

	result = init_sound_from_file(path);
	
	if (result != MA_SUCCESS) {
		ma_engine_uninit(&engine);
		cout << "sound didn't initialized\n check if path is correct";
		return -1;
	}
	cout << "sound initialized\n";

	ma_sound_start(&sound);
	cin.get();
	ma_sound_uninit(&sound);
	ma_engine_uninit(&engine);
	return 0;
}
