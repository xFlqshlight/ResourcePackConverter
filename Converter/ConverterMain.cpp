#include "helpers/Common.h"
#include "helpers/Logger.h"
#include "helpers/FileHandler.h"
#include "helpers/UUIDGen.h"
#include "Parameters.hpp"

void init() {
	_STD cout << "  _____  _____   _____                          _            " << newline;
	_STD cout << " |  __ \\|  __ \\ / ____|                        | |           " << newline;
	_STD cout << " | |__) | |__) | |     ___  _ ____   _____ _ __| |_ ___ _ __ " << newline;
	_STD cout << " |  _  /|  ___/| |    / _ \\| '_ \\ \\ / / _ \\ '__| __/ _ \\ '__|" << newline;
	_STD cout << " | | \\ \\| |    | |___| (_) | | | \\ V /  __/ |  | ||  __/ |   " << newline;
	_STD cout << " |_|  \\_\\_|     \\_____\\___/|_| |_|\\_/ \\___|_|   \\__\\___|_|   " << newline;
	_STD cout << newline;

	logger->success("Welcome to Resource Pack Converter V1.0 by Light");
	_STD cout << "This is an open-source, free, commandline application written in C++ for converting Java Edition resource packs" << newline;
	_STD cout << "to Bedrock Edition. It supports custom skies, breaking animations, potionhud fixes and experience bar cutotus." << newline;
	_STD cout << "It is still in early development and will have many updates coming soon, so stay tuned." << newline;
	_STD cout << newline;
	_STD cout << "To get started, type --help for the list of commands." << newline;
	_STD cout << newline;

}

void userInputEvent() {
	_STD unique_ptr<FilterReturnType> filter_t = _STD make_unique<FilterReturnType>();
	_STD unique_ptr<MCMETA> meta = _STD make_unique<MCMETA>();
	_STD array<std::string, RP_PARAMETER_MAX_BUFFER> temp;
	_STD string path;
	_STD string cmdInput;
	bool isNotEmpty = cmdInput.empty();
    #define CMD_CLEAR cmdInput.clear()

	while (true) { // Main Loop
		if (cmdInput.empty()) {
			_STD cout << "ResourcePackConverter/cmd >> ";
			_STD getline(_STD cin, cmdInput);
			_RP scanForParameters(cmdInput);
		}

		if (cmdInput == firstParameters[2]) { // --init
			if (_RP getManifest()) { // If manifest information successfully retrieved
				meta->getmcMetaFile(); // open file browser
			} else {
				CMD_CLEAR;
			}
			if (!meta->f_getMcMeta) { // If user exited file browser without selecting
				logger->error("Error! You didn't select a file. Please select again.");
				CMD_CLEAR;
			} else {
				_STD string __received__ = static_cast<_STD string>(meta->filename); // char[] to string
				_RP filter(__received__, filter_t); // filter to remove pack.mcmeta

				if (filter_t->filteredSuccess) { // extra debug level
					logger->success("[MAIN] Filtered Success.");
				} else { CMD_CLEAR; }
			}
			if (filter_t->filteredString.empty()) { // If filtered path doesn't exist yet
				logger->warning("Path doesn't exist yet!");
				filter_t->filteredString.clear();
			} else {
				RP_TRY // Try, incase file path is broken
					if (_RP scan(filter_t->filteredString)) {
						//fs::create_directories(path);
						logger->success("Scanning Finished.");
						filter_t->filteredString.clear();
						init();
					}
				// Catch
				RP_TRY_END RP_CATCH_EXCEPTION log(e.what()); clog_noline(_STD endl); CMD_CLEAR; RP_CATCH_EXCEPTION_END
			}
		}
		if (cmdInput == CLEAR_COMMAND) { // clear
			CMD_CLEAR;
			system("cls");
			init();
		}
		if (cmdInput == LOG_STRING_COMMAND) {
			log(_RP getCombinedString());
		}
RP_TRY
	IF_DEF_DEBUG // If debug mode

	END_IF_DEBUG
RP_TRY_END RP_CATCH_EXCEPTION log(e.what()); clog_noline(_STD endl); CMD_CLEAR; RP_CATCH_EXCEPTION_END
			if (isNotEmpty) { // If it's not empty, clear to restart the loop
				cmdInput.clear();
			}
		}
}


int main() {

	init();
	userInputEvent();

}


