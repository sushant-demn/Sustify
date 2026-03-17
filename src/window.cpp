#include "window.h"
bool play = false;
std::string cleanString(std::string clean_req) {
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), '['), clean_req.end());
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), ']'), clean_req.end());
	clean_req.erase(std::remove(clean_req.begin(), clean_req.end(), '"'), clean_req.end());
	return clean_req;
}
void bindings(webview::webview& w) {
	w.bind("searchFile", [&](std::string req) -> std::string {
		std::string path = getPath();
		//init_sound_from_file(path);
		addToQueue(path);
		play = false;
		return "\"" + path + "\"";
		});
	w.bind("stopStart", [&](std::string req) -> std::string {
		if (play) {
			ma_sound_stop(getSound());
			play = !play;
			return R"("paused")";
		}
		else {
			ma_sound_start(getSound());
			play = !play;
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
		if (getProg() == getLength())
			play = false;
		return std::to_string(getProg());
		});
	w.bind("seekSound", [&](std::string req) -> std::string {
		std::string clean_req = cleanString(req); //receive seek percentage from js
		float percentage = std::stof(clean_req); //cleaned percentage value

		setSeek(percentage * getLength());

		return "";
		});
	w.bind("getTitle", [&](std::string req)-> std::string {
		return "\"" + getTitle() + "\"";
		//return "";
		});
	w.bind("isSongEnding", [&](std::string req) -> std::string {
		if (ma_sound_at_end(getSound()))
			return R"("true")";
		return R"("false")";
		});
}
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
	LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	initEngine();
	try {
		webview::webview w(true, NULL);

		w.set_title("sustify");
		w.set_size(500, 250, WEBVIEW_HINT_FIXED);
		bindings(w);
		w.navigate("file:///E:/code/MusicStreamingApp/gui/index.html");
		w.run();
	}

	//catch (const webview::exception& e) {
	//	std::cerr << e.what() << '\n';
	//	return 1;
	//}

	catch (const webview::exception& e) {
		MessageBoxA(NULL, e.what(), "Crash Reason", MB_ICONERROR);
		return 1;
	}

	uninitAll();

	return 0;

}