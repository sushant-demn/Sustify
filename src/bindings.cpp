#include "bindings.h"

std::string cleanString(std::string clean_req) {
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), '['), clean_req.end());
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), ']'), clean_req.end());
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), '"'), clean_req.end());
	return clean_req;
}

void bindings(webview::webview& w) {
	w.bind("searchFile", [&](std::string req) -> std::string {
		std::string path = getPath();
		addToQueue(path);
		return "\"" + path + "\"";
		});
	w.bind("stopStart", [&](std::string req) -> std::string {
		if (ma_sound_is_playing(getSound())) {
			ma_sound_stop(getSound());
			return R"("paused")";
		}
		else {
			ma_sound_start(getSound());			
			return R"("playing")";
		}
		});
	w.bind("nextSong", [&](std::string req)->std::string {
		skipCurrent();
		return "\"\"";
		});
	w.bind("backSong", [&](std::string req)->std::string {
		previousSound();
		return "\"\"";;
		});
	w.bind("volumeChange", [&](std::string req) -> std::string {
		std::string clean_req = cleanString(req);
		int volumeValue = std::stoi(clean_req);
		ma_sound_set_volume(getSound(), volumeValue / 100.0f);
		return "";
		});
	w.bind("getSongLength", [&](std::string) -> std::string {
		return std::to_string(getLength());
		});
	w.bind("getCursor", [&](std::string) -> std::string {
		if (getProg() == getLength());
		return std::to_string(getProg());
		});
	w.bind("seekSound", [&](std::string req) -> std::string {
		std::string clean_req = cleanString(req); //receive seek percentage from js
		float percentage = std::stof(clean_req); //cleaned percentage value

		setSeek(percentage * getLength());

		return "";
		});
	w.bind("getTitle", [&](std::string req)-> std::string {
		//return R"("No title")";
		return "\"" + getCurrentSongTitle() + "\"";
		});
	w.bind("isSongEnding", [&](std::string req) -> std::string {
		if (ma_sound_at_end(getSound()))
			return R"("true")";
		return R"("false")";
		});

	w.bind("getQueue", [&](std::string req) -> std::string {
		return getQueue();
		});

	w.bind("addToQueue", [&](std::string req) -> std::string {
		return getLatestMeta();
		});
	w.bind("getCurrentMeta", [&](std::string req)->std::string {
		return getCurrentMeta();
		});
	w.bind("changeSong", [&](std::string req) -> std::string {
		std::string clean_req = cleanString(req);
		int index = std::stoi(clean_req);
		changeSong(index);	
		return R"("working")";
		});
}