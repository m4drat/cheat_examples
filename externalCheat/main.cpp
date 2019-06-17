#include "includes.h"
#include "getpid.h"

int main()
{
	// Find PID
	// Get process handle

	std::wstring choice;

	std::wcout << "Enter process name: ";
	std::wcin >> choice;
	std::wcout << "Searching pids of process with name: " << choice << std::endl;

	for (DWORD pid : get_pid_by_name(choice))
	{
		std::wcout << pid << std::endl;
	}
	
	std::wcin >> choice;
	return 0;
}