#include "window.h"
#include <filesystem>

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
	LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
	char pathBuffer[MAX_PATH];
	GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
	std::filesystem::path exePath = std::filesystem::absolute(pathBuffer);
	std::filesystem::path exeDir = exePath.parent_path();
	std::filesystem::path uiFilePath = exeDir / "gui" / "index.html";
	std::string absoluteUIString = uiFilePath.string();
	std::replace(absoluteUIString.begin(), absoluteUIString.end(), '\\', '/');
	std::string finalUri = "file:///" + absoluteUIString;
#else
int main() {
#endif
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	initEngine();

	try {
		webview::webview w(true, NULL);

		w.set_title("sustify");
		w.set_size(530, 260, WEBVIEW_HINT_FIXED);
		bindings(w);
		w.navigate(finalUri);
		//w.navigate("file:///E:/code/MusicStreamingApp/gui/index.html");
		w.run();
	}

	catch (const webview::exception& e) {
		MessageBoxA(NULL, e.what(), "Crash Reason", MB_ICONERROR);
		return 1;
	}

	uninitAll();

	return 0;

}