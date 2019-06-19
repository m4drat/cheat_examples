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

	// Check if DLL library exists
	if (PathFileExistsA(libraryPath.c_str()))
	{
		// Get Full path
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

	// Get Process PID by its name
	if (get_pid_by_name(psName).size() != 0)
	{
		pid = get_pid_by_name(psName)[0];
		std::wcout << "[+] 1. PID: " << pid << std::endl;

		// Open handle to process with full access
		HANDLE psHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

		if (psHandle != nullptr)
		{
			// Allocate memory for dll path in remote process
			LPVOID psMemoryLibPath = VirtualAllocEx(psHandle, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			
			// Write DLL path to newly allocated memory
			WriteProcessMemory(psHandle, psMemoryLibPath, fullLibPath, MAX_PATH, &fullLibPathSize);

			// Get address of LoadLibraryA
			FARPROC loadLibraryA = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");
			
			// Call LoadLibraryA in remote process
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