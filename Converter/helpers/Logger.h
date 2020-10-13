#pragma once
#include "Common.h"
GLOBAL_NONCONST CSTRING_CONST getProjectName() { return "[RPConverter] "; }

#define log(x) _STD cout << getProjectName() << x << "\n"
#define clog_noline(x) _STD cout << x

class Logger {
public:
	Logger()
	{
IF_DEF_DEBUG
		_STD cout << "" << newline;
END_IF_DEBUG
	}
	void error(_STD string stringInput = "", CSTRING_CONST cStringInput _NULL_PTR) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		{
			SetConsoleTextAttribute(hConsole, 4);
			if (cStringInput IS_NULL_PTR)
				_STD cout << getProjectName() << stringInput << newline;
			else
				_STD cout << getProjectName() << cStringInput << newline;
			
		}
		// Back to Normal
		SetConsoleTextAttribute(hConsole, 7);
		return;
	}
	void warning(_STD string stringInput = "", CSTRING_CONST cStringInput _NULL_PTR) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		{

			SetConsoleTextAttribute(hConsole, 6);
			if (cStringInput IS_NULL_PTR)
				_STD cout << getProjectName() << stringInput << newline;
			else
				_STD cout << getProjectName() << cStringInput << newline;
		}
		// Back to Normal
		SetConsoleTextAttribute(hConsole, 7);
		return;
	}
	void success(std::string stringInput = "", CSTRING_CONST cStringInput _NULL_PTR) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		{
			SetConsoleTextAttribute(hConsole, 2);
			if (cStringInput IS_NULL_PTR)
				_STD cout << getProjectName() << stringInput << newline;
			else
				_STD cout << getProjectName() << cStringInput << newline;
		}
		// Back to Normal
		SetConsoleTextAttribute(hConsole, 7);
		return;
	}
}; GLOBAL_NONCONST _STD unique_ptr<Logger> logger = _STD make_unique<Logger>();
