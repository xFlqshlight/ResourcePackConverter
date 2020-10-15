#pragma once
#include "Parameters.hpp"
#include "helpers/Common.h"
#include "helpers/Common.h"
#include "helpers/Logger.h"
#include "helpers/FileHandler.h"
#include "helpers/UUIDGen.h"

namespace RP {
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

	struct CombinedParams {
		bool f_finishedCombined{}; // finished combined?
		STRING Com_String; // combined string
		size_t count_t;

		// Store each parameter in a string for later purposes
		_STD string firstParameter;
		_STD string secondParameter;
		_STD string thirdParameter;
		_STD string optionalParameter;
		_STD string extraParameter;
	} combinedParams;

	_STD string getCombinedString() { return combinedParams.Com_String; }

	_STD string ConCat(CSTRING_NONCONST f[], CSTRING_NONCONST s[], CSTRING_NONCONST th[], CSTRING_NONCONST op[], CSTRING_NONCONST ex[]) {
		_STD string newf, news, newth, newop, newex;
		_STD string error = "Can't cast C-strings to std::string";
		RP_TRY
		newf = static_cast<_STD string>(f);
		news = static_cast<_STD string>(s);
		newth = static_cast<_STD string>(th);
		newop = static_cast<_STD string>(op);
		newex = static_cast<_STD string>(ex);
		RP_TRY_END RP_CATCH_EXCEPTION throw error; combinedParams.f_finishedCombined = false; RP_CATCH_EXCEPTION_END

		combinedParams.f_finishedCombined = true;
		return newf + STDSPACE + news + STDSPACE + newth + STDSPACE + newop + STDSPACE + newex;
	}

	bool Transfer(CSTRING_NONCONST f[], CSTRING_NONCONST s[], CSTRING_NONCONST th[], CSTRING_NONCONST op[], CSTRING_NONCONST ex[]) {
		_STD string newf, news, newth, newop, newex;

		RP_TRY
		newf = static_cast<_STD string>(f);
		news = static_cast<_STD string>(s);
		newth = static_cast<_STD string>(th);
		newop = static_cast<_STD string>(op);
		newex = static_cast<_STD string>(ex);

		combinedParams.firstParameter = newf;
		combinedParams.secondParameter = news;
		combinedParams.thirdParameter = newth;
		combinedParams.optionalParameter = newop;
		combinedParams.extraParameter = newex;
		RP_TRY_END RP_CATCH_EXCEPTION log(e.what()); return false; RP_CATCH_EXCEPTION_END

		return true;
	}

	VOID scanForParameters(STRING& input) {
		// Buffers 
		CSTRING_NONCONST f_paramBuffer[RP_PARAMETER_MAX_BUFFER];
		CSTRING_NONCONST s_paramBuffer[RP_PARAMETER_MAX_BUFFER];
		CSTRING_NONCONST th_paramBuffer[RP_PARAMETER_MAX_BUFFER];
		CSTRING_NONCONST op_paramBuffer[RP_PARAMETER_MAX_BUFFER];
		CSTRING_NONCONST ex_paramBuffer[RP_PARAMETER_MAX_BUFFER];

		// Checks
		bool hasFirstParameter{};
		STRING f_p;
		bool hasSecondParameter{};
		STRING s_p;
		bool hasThirdParameter{};
		STRING th_p;
		bool hasOptionalParameter{};
		STRING op_p;
		bool hasExtraParameter{};
		STRING ex_p; // Probably not gonna get used

		#define FIRST_PARAMETER f_p
		#define SECOND_PARAMETER s_p
		#define THIRD_PARAMETER th_p
		#define OPTIONAL_PARAMETER op_p
		#define EXTRA_PARAMETER ex_p

		int dupCountF{};
		int dupCountS{};
		int dupCountTH{};
		int dupCountOP{};
		int dupCountEX{};

		/*---------------------------
		  FIRST PARAMETER CHECKER. 
		----------------------------*/
	
		for (int it = 0; it < firstParameters.size(); it++) { // Searches for first parameter in our input string
			size_t ParamExists = input.find(firstParameters[it]);

			if (ParamExists IS_NOT std::string::npos) { // If found, do
				f_p = firstParameters[it];
				hasFirstParameter = true;
				dupCountF = it; // store the value to dupCountF (dupCountFirst) for duplicate purposes
				if (dupCountF IS 0) { dupCountF++; } // If dupCountF stored 0 (first element in our FirstParameters_
				// add 1 so it won't break

				IF_DEF_DEBUG
				std::cout << "Found first parameter: " << f_p << newline;
				std::cout << "dupCountF: " << dupCountF << newline;
				END_IF_DEBUG
				break;
			}
		}
		// If "--help" is on string f_p, start at 0 + dupCountF to include the parameter string next to "--help", otherwise start at 1 + dupCountF
		// I honestly don't know how this worked, lol
		for (int second = (f_p IS "--help") ? 0 + dupCountF : 1 + dupCountF; second < firstParameters.size(); second++) { // Check for duplicate parameters
			size_t DuplicateExists = input.find(firstParameters[second]);

			if (DuplicateExists IS_NOT std::string::npos) {
				IF_DEF_DEBUG
				std::cout << "Found duplicate parameter: " << firstParameters[second] << newline;
				std::cout << "second: " << second << newline;
				END_IF_DEBUG
				logger->warning(PARAMETER_ERROR_CODE_1);
				break;
			}
			dupCountF = 0;
		}
		bool cantFind{};
		if (!hasFirstParameter) { // Find duplicate parameter
			for (int third = 0; third < firstParameters.size(); third++) {
				_STD string prefix = "--";
				size_t hasPrefix = input.find(prefix);
				size_t UnknownParameter = input.find(firstParameters[third]);
	
				if (hasPrefix IS_NOT std::string::npos) { // Must find prefix first
					if (third < firstParameters.size() && UnknownParameter IS std::string::npos) { 
						cantFind = true; // We don't care about how much this iterates
					}
				}

			} if (cantFind) logger->warning(PARAMETER_ERROR_CODE_2);
	     }

		/*---------------------------
		  SECOND PARAMETER CHECKER.
		----------------------------*/
		for (int it = 0; it < secondParameters.size(); it++) { // Searches for second parameter in our input string
			size_t ParamExists = input.find(secondParameters[it]);

			if (ParamExists IS_NOT std::string::npos) { // If found, do
				s_p = secondParameters[it];
				hasSecondParameter = true;
				dupCountS = it; // store the value to dupCountS (dupCountSecond) for duplicate purposes
				if (dupCountS IS 0) { dupCountS++; } // If dupCountS stored 0 (first element in our SecondParameters_
				// add 1 so it won't break

				IF_DEF_DEBUG
					std::cout << "Found second parameter: " << s_p << newline;
				    std::cout << "dupCountS: " << dupCountS << newline;
				END_IF_DEBUG
					break;
			}
		}
	IF_DEF_(hasFirstParameter AND hasSecondParameter)
		for (int second = (s_p IS "to_bedrock") ? 0 + dupCountS : 1 + dupCountS; second < secondParameters.size(); second++) { // Check for duplicate parameters
			size_t DuplicateExists = input.find(secondParameters[second]);

			if (DuplicateExists IS_NOT std::string::npos) {
				IF_DEF_DEBUG
					std::cout << "Found duplicate parameter: " << secondParameters[second] << newline;
				    std::cout << "second: " << second << newline;
				END_IF_DEBUG
					logger->warning(PARAMETER_ERROR_CODE_1);
				break;
			}
			dupCountS = 0;
		}
		bool cantFindSecond{};
		if (!hasSecondParameter) { // Find duplicate parameter
			for (int third = 0; third < secondParameters.size(); third++) {
				size_t UnknownParameter = input.find(secondParameters[third]);
				if (third < secondParameters.size() && UnknownParameter IS std::string::npos) {
					cantFindSecond = true; // We don't care about how much this iterates
				}
			} if (cantFindSecond) logger->warning(PARAMETER_ERROR_CODE_3);
		}
	IF_DEF_END

		/*---------------------------
		COMPATIBILE PARAMETER CHECKER.
		----------------------------*/

		if (f_p IS CONVERT_COMMAND AND s_p IS_NOT TO_BEDROCK) {
			logger->error(PARAMETER_ERROR_CODE_4);
		}

		if (f_p IS HELP_COMMAND AND hasSecondParameter) {
			logger->warning("Help command doesn't accept any parameters");
		}

		if (FIRST_PARAMETER == ITERATE_COMMAND && (SECOND_PARAMETER != DIRECTORYLIST && SECOND_PARAMETER != COMMANDLIST)) {
			logger->error(PARAMETER_ERROR_CODE_4);
		}
		
		/*---------------------------
		  THIRD PARAMETER CHECKER.
		----------------------------*/

		/*---------------------------
		  OPTIONAL PARAMETER CHECKER.
		----------------------------*/

		/*---------------------------
		  EXTRA PARAMETER CHECKER.
		----------------------------*/
		bool stillCheckingExtraParameters{};

		IF_DEF_(!stillCheckingExtraParameters)
			if (input == CLEAR_COMMAND) { // clear
				input.clear();
				system("cls");
				init();
				stillCheckingExtraParameters = true;
			}
			if (input == LOG_STRING_COMMAND) {
				log(_RP getCombinedString());
				stillCheckingExtraParameters = true;
			}
			if (input == DISPLAY_SECOND_PARAMETER) {
				std::cout << combinedParams.secondParameter << newline;
				stillCheckingExtraParameters = true;
			}
		IF_DEF_END

	    // Debug purposes
		bool shouldOutPutThis = 0;
		
		IF_DEF_(shouldOutPutThis)
			clog_noline(_STD boolalpha);
		_STD cout << hasFirstParameter << CSPACE << hasSecondParameter << CSPACE << hasThirdParameter << CSPACE
			<< hasOptionalParameter << CSPACE << hasExtraParameter << newline;
		IF_DEF_END

		strcpy_s(f_paramBuffer, RP_PARAMETER_MAX_BUFFER, f_p.c_str());
		strcpy_s(s_paramBuffer, RP_PARAMETER_MAX_BUFFER, s_p.c_str());
		strcpy_s(th_paramBuffer, RP_PARAMETER_MAX_BUFFER, th_p.c_str());
		strcpy_s(op_paramBuffer, RP_PARAMETER_MAX_BUFFER, op_p.c_str());
		strcpy_s(ex_paramBuffer, RP_PARAMETER_MAX_BUFFER, ex_p.c_str());

		RP_TRY
		// Store the new string to combined string
		combinedParams.Com_String = ConCat(f_paramBuffer, s_paramBuffer, th_paramBuffer, op_paramBuffer, ex_paramBuffer);
		RP_TRY_END catch (std::string error) { logger->error(error); }

		// Transfer buffers to strings, perhaps use them, returns false or true
		if (Transfer(f_paramBuffer, s_paramBuffer, th_paramBuffer, op_paramBuffer, ex_paramBuffer) && combinedParams.f_finishedCombined) {
			// Clear buffers
			memset(f_paramBuffer, 0, RP_PARAMETER_MAX_BUFFER);
			memset(s_paramBuffer, 0, RP_PARAMETER_MAX_BUFFER);
			memset(th_paramBuffer, 0, RP_PARAMETER_MAX_BUFFER);
			memset(op_paramBuffer, 0, RP_PARAMETER_MAX_BUFFER);
			memset(ex_paramBuffer, 0, RP_PARAMETER_MAX_BUFFER);
		}

		IF_DEF_(shouldOutPutThis)
			_STD cout << combinedParams.Com_String << newline;
		IF_DEF_END
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
				}
				else {
					CMD_CLEAR;
				}
				if (!meta->f_getMcMeta) { // If user exited file browser without selecting
					logger->error("Error! You didn't select a file. Please select again.");
					CMD_CLEAR;
				}
				else {
					_STD string __received__ = static_cast<_STD string>(meta->filename); // char[] to string
					_RP filter(__received__, filter_t); // filter to remove pack.mcmeta

					if (filter_t->filteredSuccess) { // extra debug level
						logger->success("[MAIN] Filtered Success.");
					}
					else { CMD_CLEAR; }
				}
				if (filter_t->filteredString.empty()) { // If filtered path doesn't exist yet
					logger->warning("Path doesn't exist yet!");
					filter_t->filteredString.clear();
				}
				else {
					RP_TRY // Try, incase file path is broken
						if (_RP scan(filter_t->filteredString)) {
							//fs::create_directories(path);
							logger->success("Scanning Finished.");
							filter_t->filteredString.clear();
							_RP init();
						}
					// Catch
					RP_TRY_END RP_CATCH_EXCEPTION log(e.what()); clog_noline(_STD endl); CMD_CLEAR; RP_CATCH_EXCEPTION_END
				}
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
}
