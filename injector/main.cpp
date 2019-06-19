#include "getpid.h"

int main()
{
	DWORD pid;
	std::wstring psName;
	std::string libraryPath;
	TCHAR fullLibPath[MAX_PATH];
	size_t fullLibPathSize = 0;

	std::wcout << "[+] Enter path to DLL you want to inject: ";
	std::cin >> libraryPath;

	// Ch
	if (PathFileExistsA(libraryPath.c_str()))
	{
		fullLibPathSize = GetFullPathNameA(libraryPath.c_str(), MAX_PATH, fullLibPath, NULL);
	}
	else {
		std::wcout << "[-] Check library path!\n";
		getchar();
		return 3;
	}

	std::wcout << "[+] Enter process name: ";
	std::wcin >> psName;
	std::wcout << "[+] Searching pids of process with name: " << psName << std::endl;

	if (get_pid_by_name(psName).size() != 0)
	{
		pid = get_pid_by_name(psName)[0];
		std::wcout << "[+] 1. PID: " << pid << std::endl;
		HANDLE psHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

		if (psHandle != nullptr)
		{
			LPVOID psMemoryLibPath = VirtualAllocEx(psHandle, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			WriteProcessMemory(psHandle, psMemoryLibPath, fullLibPath, MAX_PATH, &fullLibPathSize);

			FARPROC loadLibraryA = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");
			CreateRemoteThread(psHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryA, psMemoryLibPath, NULL, NULL);
		}
		else {
			std::wcout << "[-] Cannot open process.\n";
			std::wcout << "[-] Check your privilegies.\n";
			getchar();
			return 2;
		}
	}
	else {
		std::wcout << "[-] Cannot find any process!\n";
		getchar();
		return 1;
	}
}