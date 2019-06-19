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

	std::wcout << "Searching pids of process with name: " << psName << std::endl;

	int cnt = 0;
	for (DWORD pid : get_pid_by_name(psName))
	{
		cnt++;
		std::wcout << "[+] " << cnt << ". PID: " << pid << std::endl;
	}
	if (cnt == 0)
		std::wcout << "[-] Cannot find any process!\n";
	
	std::wcin >> psName;
	return 0;
}