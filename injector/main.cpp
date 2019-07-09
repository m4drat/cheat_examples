#include "getpid.h"

int main()
{
	std::wstring psName;
	std::string libraryPath;
	TCHAR fullLibPath[MAX_PATH];
	size_t fullLibPathSize = 0;
	std::vector <DWORD> pids;

	for (;;)
	{
		std::wcout << "[+] Enter path to DLL you want to inject: ";
		std::cin >> libraryPath;

		// Check if DLL library exists
		if (PathFileExistsA(libraryPath.c_str()))
		{
			// Get Full path
			fullLibPathSize = GetFullPathNameA(libraryPath.c_str(), MAX_PATH, fullLibPath, NULL);
			break;
		}
		else {
			std::wcout << "[-] Check library path!\n";
		}
	}

	for (;;)
	{
		std::wcout << "[+] Enter process name: ";
		std::wcin >> psName;
		std::wcout << "[+] Searching pids of process with name: " << psName << std::endl;

		// Get Process PID by its name
		pids = get_pid_by_name(psName);

		if (pids.size() == 0) {
			std::wcout << "[-] Cannot find any process!\n";
		}
		else {
			std::wcout << "[+] 1. PID: " << pids[0] << std::endl;
			break;
		}
	}

	// Open handle to process with full access
	HANDLE psHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pids[0]);

	if (psHandle != nullptr)
	{
		// Allocate memory for dll path in remote process
		LPVOID psMemoryLibPath = VirtualAllocEx(psHandle, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			
		if (psMemoryLibPath != nullptr)
		{
			// Write DLL path to newly allocated memory
			WriteProcessMemory(psHandle, psMemoryLibPath, fullLibPath, MAX_PATH, &fullLibPathSize);

			// Get address of LoadLibraryA
			FARPROC loadLibraryA = GetProcAddress(GetModuleHandle("kernel32"), "LoadLibraryA");

			// Call LoadLibraryA in remote process to load DLL
			CreateRemoteThread(psHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryA, psMemoryLibPath, NULL, NULL);

			printf("[+] Remote thread in process with pid: %d created!\n", pids[0]);
		}
		else {
			std::wcout << "[-] Something went wrong.\n";
			return 2;
		}
		
	}
	else {
		std::wcout << "[-] Cannot open process.\n";
		std::wcout << "[-] Check your privilegies.\n";
		getchar();
		return 2;
	}
}