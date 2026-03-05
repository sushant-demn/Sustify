#include "file_system.h"

std::string getPath() {

	if (!pfd::settings::available()) {
		std::cout << "Portable File Dialogs are not available on this platform.\n";
		return "";
	}

	auto selection = pfd::open_file("Select a Music File", ".",
		{ "Audio Files", "*.mp3 *.wav *.flac",
			"All Files", "*" }).result();

	if (!selection.empty()) {
		std::replace(selection[0].begin(), selection[0].end(), '\\', '/');
		return selection[0];
	}
	if (selection.empty())
		return "selection cancelled";
	return "";
}
