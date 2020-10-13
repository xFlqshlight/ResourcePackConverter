#pragma once
#include "helpers/Common.h"

_STD map<int, _STD string> warnings = { // Int = warning code, string = warning
	_STD pair<int, _STD string>(1, "--convert <platform> <include> <optionalInclude> [See --help for include parameters]"),
	_STD pair<int, _STD string>(2, "--help <page>"),
	_STD pair<int, _STD string>(3, "--info [OPTIONAL]<parameter>"),
	_STD pair<int, _STD string>(4, "--getStatus <target> [See --help for target parameters]"),
	_STD pair<int, _STD string>(5, "--iterate <list> [See --help for list parameters]")
};

_STD map<int, _STD string> errors = { // Int = error code, string = error
	_STD pair<int, _STD string>(1, "Duplicate first parameters!"),
	_STD pair<int, _STD string>(2, "Unknown first parameter "),
	_STD pair<int, _STD string>(3, "Duplicate parameter ")
};

// Error codes
#define PARAMETER_ERROR_CODE_1 errors.find(1)->second
#define PARAMETER_ERROR_CODE_2 errors.find(2)->second
#define PARAMETER_ERROR_CODE_3 errors.find(3)->second
#define PARAMETER_WARNING_CODE_1 warnings.find(1)->second
#define PARAMETER_WARNING_CODE_2 warnings.find(2)->second
#define PARAMETER_WARNING_CODE_3 warnings.find(3)->second
#define PARAMETER_WARNING_CODE_4 warnings.find(4)->second
#define PARAMETER_WARNING_CODE_5 warnings.find(5)->second

_STD vector<_STD string> firstParameters = { // --
	("--help"), // 0
	("--convert"),// 1
	("--init"),// 2
	("--info"),// 3
	("--iterate"), // 4
	("--getStatus") // 5
};

_STD vector<_STD string> secondParameters = { // __
	("to_bedrock"),// 0
	("directoryList"), // 1
	("commandList"), // 2
	("filteredSuccess"), // 3
	("mcMetaExists"), // 4
	("filteredString"), // 5
	("f_getMcMeta") // 6
};

_STD vector<_STD string> thirdParameters = { // -
	("-include"),// 0
};

_STD vector<_STD string> optionalParameters = {
	("astral"),// 0
	("java_ui"),// 1
	("sildursbasic"),// 2
	("-settings"),// 3
	("bedrocksky"),// 4
	("javasky"),// 5
	("nocubemap"),// 6
	("nopocketwidgets"),// 7
	("nopotioneffects"),// 8
	("nobreakinganims"),// 9
	("cubemap"),// 10
	("pocketwidgets"),// 11
	("potioneffects"),// 12
	("breakinganims"),// 13
};

_STD vector<_STD string> extraParameters = {
	("clear"),// 0
	("log string") //1
};
