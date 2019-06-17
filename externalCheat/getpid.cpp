#include "getpid.h"

std::vector<DWORD> get_pid_by_name(std::wstring targetName)
{
	std::vector<DWORD> pids;

	DWORD targetPid;
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32W entry;
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry)) { //start with the first in snapshot
		return std::vector<DWORD>();
	}

	do {
		if (std::wstring(entry.szExeFile) == targetName) {
			pids.emplace_back(entry.th32ProcessID); //name matches; add to list
		}
	} while (Process32NextW(snap, &entry)); //keep going until end of snapshot

	return pids;
}