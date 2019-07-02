#include "PatternScan.h"

void PatternScan::get_module_info(std::string moduleName, MODULEINFO& modInfo)
{
	HMODULE hModule = nullptr;

	GetModuleHandleEx(0, moduleName.c_str(), &hModule);
	GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
}

DWORDLONG PatternScan::find_pattern_static(MODULEINFO module, const char* pattern, const char* mask)
{
	DWORDLONG base = (DWORDLONG)module.lpBaseOfDll;
	DWORDLONG size = module.SizeOfImage;
	DWORD patternLength = DWORD(strlen(mask));

	for (DWORDLONG i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (DWORDLONG j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
		}
		if (found)
		{
			return base + i;
		}
	}
	return NULL;
}

DWORDLONG PatternScan::find_pattern_internal(std::string pattern)
{
	auto mbi = MEMORY_BASIC_INFORMATION();
	DWORDLONG curr_addr = 0;

	while (true)
	{
		if (VirtualQuery(reinterpret_cast<const void*>(curr_addr), &mbi, sizeof mbi) == 0)
		{
			break;
		}

		if ((mbi.State == MEM_COMMIT || mbi.State == MEM_RESERVE) &&
			(mbi.Protect == PAGE_READONLY ||
				mbi.Protect == PAGE_READWRITE ||
				mbi.Protect == PAGE_EXECUTE_READ ||
				mbi.Protect == PAGE_EXECUTE_READWRITE))
		{
			auto result = PatternScan::find_pattern_internal_in_range(pattern, reinterpret_cast<DWORDLONG>(mbi.BaseAddress), reinterpret_cast<DWORDLONG>(mbi.BaseAddress) + mbi.RegionSize);

			if (result != NULL)
			{
				return result;
			}
		}

		curr_addr += mbi.RegionSize;
	}

	return NULL;
}

DWORDLONG PatternScan::find_pattern_internal_in_range(std::string pattern, const DWORDLONG range_start, const DWORDLONG range_end)
{
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

	for (auto p_cur = range_start; p_cur < range_end; p_cur++)
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

			auto neededValue = static_cast<char>(value);
			auto pCurrentValue = reinterpret_cast<char*>(localAddr);
			auto currentValue = *pCurrentValue;

			if (neededValue != currentValue)
			{
				found = false;
				break;
			}

			localAddr += 1;
		}

		if (found)
		{
			return p_cur;
		}
	}
	return NULL;
}

