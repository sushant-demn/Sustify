
/*
	For now this queuing system
	1. Just plays the song if no songs is playing and no song is in queue.
	2. Adds to the queue is song is playing and queue is empty or not empty.
	3. Loops the queue from first to last song again and again.
	4. Can Skip to next song.
	5. Can Skip back to previous song if the progress of the current on is under 3 sec or start the current Song again.

	Plan
	1. Add a good suffling method.
	2. Add single loop and queue loop.
*/

#include "queue.h"

std::deque<track> queue;

int currentCursor = -1;

track buildTrack(std::string path) {
	track t;

	t.path = path;
	t.title = path.substr(path.find_last_of("/\\") + 1);
	t.artist = "Unkown Artist";
	//t.duration = getLength()
	t.title = getTitle(path);
	return t;
}

void addToQueue(std::string path) {
	if (queue.empty() && !checkPlaying())
	{
		queue.push_back(buildTrack(path));
		currentCursor++;
		init_sound_from_file(path);
	}

	else
		queue.push_back(buildTrack(path));

}
void skipCurrent() { //skips to next song. 
	if (!queue.empty())
	{
		currentCursor = (currentCursor + 1) % queue.size();
		init_sound_from_file(queue[currentCursor].path);
	}
}

void previousSound() { //skips to the previous song if current song progress is under 3 second.
	if (!queue.empty())
	{
		if (getProg() >= 3.0f) {
			ma_sound_seek_to_second(getSound(), 0.0f);
		}
		else
		{
			currentCursor = (currentCursor - 1 + queue.size()) % queue.size();
			init_sound_from_file(queue[currentCursor].path);
		}
	}
}

std::string getQueue() {
	if (queue.empty()) {
		return "[]";
	}
	std::string jsonArray = "[";

	for (int i = 0; i < queue.size(); i++)
	{
		jsonArray += "\"" + queue[i].title + "\"";

		if (i < queue.size() - 1)
			jsonArray += ",";
	}
	jsonArray += "]";
	return jsonArray;
}

std::string getCurrentSongPath() {
	return queue[currentCursor].path;
}

std::string getCurrentSongTitle() {
	return queue[currentCursor].title;
}

std::string getCurrentSongArtist() {
	return queue[currentCursor].artist;
}
std::string getLatestMeta() {
	if (queue.empty())
		return "[]";

	std::string jsonArray = "[";
	jsonArray += "\"" + queue.back().title + "\"";
	jsonArray += ",";
	jsonArray += "\"" + queue.back().artist + "\"";
	jsonArray += ",";
	jsonArray += "\"" + queue.back().path + "\"";
	jsonArray += ",";
	jsonArray += "\"" + std::to_string(queue.size() - 1) + "\"";
	jsonArray += "]";

	return jsonArray;

}
std::string getCurrentMeta() {
	if (queue.empty())
		return "[]";

	std::string jsonArray = "[";
	jsonArray += "\"" + queue[currentCursor].title + "\"";
	jsonArray += ",";
	jsonArray += "\"" + queue[currentCursor].artist + "\"";
	jsonArray += ",";
	jsonArray += "\"" + queue[currentCursor].path + "\"";
	jsonArray += ",";
	jsonArray += "\"" + std::to_string(currentCursor) + "\"";
	jsonArray += "]";

	return jsonArray;
}

void changeSong(int cursor) {
	currentCursor = cursor;	
	init_sound_from_file(queue[cursor].path);
}