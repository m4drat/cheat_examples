#include <iostream>
#include <Windows.h>

#include "getpid.h"
#include "ExternalCheat.h"

int main()
{
	std::wstring psName;
	std::vector <DWORD> pids;

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
	
	ExternalCheat* cheat = ExternalCheat::get_instance();
	if (cheat->init(pids[0]))
	{
		std::wcout << "[+][CH] Cheat loaded successfully!\n";
		cheat->exec();
	}
	else {
		std::wcout << "[-] Player Signature Cannot be found!" << "\n> ";
	}
}