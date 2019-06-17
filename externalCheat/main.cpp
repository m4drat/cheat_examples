#include "includes.h"
#include "getpid.h"

int main()
{
	// Find PID
	// Get process handle

	std::wstring psName;
	std::wstring inGameName;

	std::wcout << "Enter process name: ";
	std::wcin >> psName;

	std::wcout << "Enter your in-game name: ";
	std::wcin >> inGameName;

	std::wcout << "Searching pids of process with name: " << psName << std::endl;

	for (DWORD pid : get_pid_by_name(psName))
	{
		std::wcout << "[+] PID: " << pid << std::endl;
	}
	
	std::wcin >> psName;
	return 0;
}