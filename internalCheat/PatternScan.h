#pragma once

#include <sstream>
#include <vector>
#include "Shlwapi.h"
#include <psapi.h>
#include <Windows.h>
#include <tlhelp32.h>

class PatternScan
{
private:

public:
	// Searh in static memory (not stack or heap)
	// moduleName - name of module (game.exe), modInfo - structure which will be filled up
	static void get_module_info(std::string moduleName, MODULEINFO& modInfo);

	// Searh in static memory (not stack or heap)
	// Find pattern in specific module 
	// void* ammoDecAddress = FindPattern(L"bf4.exe", L"\x89\x93\x00\x00\x00\x00\x00\x9d", L"xx????xx");
	static DWORDLONG find_pattern_static(MODULEINFO module, const char* pattern, const char* mask);
	
	// Find pattern in process memory
	// player_base_ = reinterpret_cast<void*>(find_pattern("ED 03 ?? ?? 01 00 00 00"));
	// ?? - unknown bytes
	static DWORDLONG find_pattern_internal(std::string pattern);

	// Find pattern in specific memory range
	static DWORDLONG find_pattern_internal_in_range(std::string pattern, const DWORDLONG range_start, const DWORDLONG range_end);
};