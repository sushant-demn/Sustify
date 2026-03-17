
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

std::deque<std::string> queue;

int currentCursor = -1;

void addToQueue(std::string path) {
	if (queue.empty() && !checkPlaying())
	{
		queue.push_back(path);
		currentCursor++;
		init_sound_from_file(path);
	}

	else
		queue.push_back(path);

}
void skipCurrent() { //skips to next song.
	if (!queue.empty())
	{
		currentCursor = (currentCursor + 1) % queue.size();
		init_sound_from_file(queue[currentCursor]);
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
			init_sound_from_file(queue[currentCursor]);
		}
	}
}

std::string getCurrentSongPath() {
	return queue[currentCursor];
}