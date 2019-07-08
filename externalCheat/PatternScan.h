#pragma once

#include <sstream>
#include <vector>
#include "Shlwapi.h"
// #include <psapi.h>
#include <Windows.h>
// #include <tlhelp32.h>

class PatternScan
{
private:

public:
	// Get all memory regions of target process
	static std::vector<_MEMORY_BASIC_INFORMATION *> query_memory_regions(HANDLE psHandle);

	// Find pattern in process memory
	// player_base_ = reinterpret_cast<void*>(find_pattern("ED 03 ?? ?? 01 00 00 00"));
	// ?? - unknown bytes
	static DWORDLONG find_pattern_external(HANDLE psHandle, std::string pattern);

	// Find pattern in specific memory range
	static DWORDLONG find_pattern_external_in_range(HANDLE psHandle, _MEMORY_BASIC_INFORMATION* cur_mbi, std::string pattern);
};