#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <commdlg.h>
#include <random>
#include <sstream>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include "../include/json.hpp"

// Convenience
namespace fs = std::filesystem;
using json = nlohmann::json;

// Debug or not
inline extern const bool debug = 1;

// Convenient macro
#define newline '\n'
#define CSPACE ' '
#define STDSPACE " "

// For some reason <filesystem> breaks when it's release mode, so I can't use #ifdef _DEBUG in project properties
// So I resort to this
#define IF_DEF_DEBUG if (debug) {
#define END_IF_DEBUG }

#define IF_DEF_(x) if (x) {
#define IF_DEF_END }

// Catch Exceptions
#define RP_TRY try {
#define RP_TRY_END }
#define RP_CATCH_EXCEPTION catch (std::exception e) {
#define RP_CATCH_EXCEPTION_END }

// Our own Max path and buffer macro
#define RP_MAX_PATH 500
#define RP_PARAMETER_MAX_BUFFER 50

// Handy Macros
#define STRING std::string
#define CSTRING_CONST const char*
#define CSTRING_NONCONST char
#define GLOBAL_CONST inline extern const
#define GLOBAL_NONCONST inline extern
#define VOID void
#define VOID_PTR void*
#define IS_NULL_PTR == nullptr
#define _NULL_PTR = nullptr

// Logical Macros
#define AND &&
#define OR ||
#define IS ==
#define IS_NOT !=