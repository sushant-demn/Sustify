#include "window.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
	LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
	try {
		webview::webview w(false, NULL);

		w.set_title("test window");
		w.set_size(500, 250, WEBVIEW_HINT_FIXED);
		//w.set_html(R"(<h1 style="text-color:black">this is a test window</ht>)");
		w.navigate("file:///E:/code/MusicStreamingApp/gui/index.html");
		w.run();
	}
	catch (const webview::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}


	return 0;

}