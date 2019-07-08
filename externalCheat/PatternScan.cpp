#include "PatternScan.h"

std::vector<_MEMORY_BASIC_INFORMATION*> PatternScan::query_memory_regions(HANDLE psHandle)
{
	std::vector<_MEMORY_BASIC_INFORMATION *> regions;
	DWORDLONG curr_addr = 0;

	for (;;)
	{
		_MEMORY_BASIC_INFORMATION *mbi = new _MEMORY_BASIC_INFORMATION;

		if (VirtualQueryEx(psHandle, reinterpret_cast<const void*>(curr_addr), mbi, sizeof _MEMORY_BASIC_INFORMATION) == 0)
		{
			break;
		}

		if ((mbi->State == MEM_COMMIT || mbi->State == MEM_RESERVE) &&
			(mbi->Protect == PAGE_READONLY ||
				mbi->Protect == PAGE_READWRITE ||
				mbi->Protect == PAGE_EXECUTE_READ ||
				mbi->Protect == PAGE_EXECUTE_READWRITE))
		{
			regions.push_back(mbi);
		}

		curr_addr += mbi->RegionSize;
	}

	return regions;
}

DWORDLONG PatternScan::find_pattern_external(HANDLE psHandle, std::string pattern)
{
	DWORDLONG curr_addr = 0;
	std::vector<_MEMORY_BASIC_INFORMATION*> regions = query_memory_regions(psHandle);

	for (_MEMORY_BASIC_INFORMATION *cur_region : regions)
	{
		auto result = PatternScan::find_pattern_external_in_range(psHandle, cur_region, pattern);

		if (result != NULL)
		{
			return result;
		}
	}

	return NULL;
}

DWORDLONG PatternScan::find_pattern_external_in_range(HANDLE psHandle, _MEMORY_BASIC_INFORMATION* cur_mbi, std::string pattern)
{

	// Allocate buffer for saved process memory
	byte* memory = new byte[cur_mbi->RegionSize];

	if (memory == nullptr)
	{
		delete[] memory;
		return NULL;
	}

	if (!ReadProcessMemory(psHandle, cur_mbi->BaseAddress, memory, cur_mbi->RegionSize, NULL))
	{
		delete[] memory;
		return NULL;
	}

	auto strstream = std::istringstream(pattern);

	std::vector<int> values;
	std::string s;

	while (getline(strstream, s, ' '))
	{
		if (s.find("??") != std::string::npos)
		{
			values.push_back(-1);
			continue;
		}

		auto parsed = std::stoi(s, 0, 16);
		values.push_back(parsed);
	}

	for (size_t p_cur = 0; p_cur < cur_mbi->RegionSize - values.size(); p_cur++)
	{
		auto localAddr = p_cur;
		auto found = true;

		for (auto value : values)
		{
			if (value == -1)
			{
				localAddr += 1;
				continue;
			}

			char neededValue = static_cast<char>(value);
			char currentValue = memory[localAddr];

			if (neededValue != currentValue)
			{
				found = false;
				break;
			}

			localAddr += 1;
		}

		if (found)
		{
			delete[] memory;
			return p_cur + reinterpret_cast<DWORDLONG>(cur_mbi->BaseAddress);
		}
	}

	delete[] memory;
	return NULL;
}