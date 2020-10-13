#pragma once
#include "Vectors.hpp"
#include "helpers/Common.h"

namespace RP {
	struct CombinedParams {
		bool f_finishedCombined{};
		STRING Com_String;
		size_t count_t;

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

		int dupCountF{};

		for (int it = 0; it < firstParameters.size(); it++) { // Searches for first parameter in our input string
			size_t ParamExists = input.find(firstParameters[it]);

			if (ParamExists != _STD string::npos) { // If found, do
				f_p = firstParameters[it];
				hasFirstParameter = true;
				dupCountF = it; // store the value to dupCountF (dupCountFirst) for duplicate purposes
				if (dupCountF == 0) { dupCountF++; } // If dupCountF stored 0 (first element in our FirstParameters_
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
		for (int second = (f_p == "--help") ? 0 + dupCountF : 1 + dupCountF; second < firstParameters.size(); second++) { // Check for duplicate parameters
			size_t DuplicateExists = input.find(firstParameters[second]);

			if (DuplicateExists != _STD string::npos) {
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
	
				if (hasPrefix != _STD string::npos) { // Must find prefix first
					if (third < firstParameters.size() && UnknownParameter == _STD string::npos) { 
						cantFind = true; // We don't care about how much this iterates
					}
				}

			} if (cantFind) logger->warning(PARAMETER_ERROR_CODE_2);
	     }
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
}
