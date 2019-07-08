#include <iostream>
#include <Windows.h>

#include "InternalCheat.h"

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		InternalCheat *cheat = InternalCheat::get_instance();
		if (cheat->init())
		{
			std::wcout << "[+][CH] Cheat loaded successfully!\n";
			// MessageBox(NULL, "Cheat Successfully Initialized!", "Cheat", MB_OK);
			cheat->exec();
		}
		else {
			std::wcout << "[-] Player Signature Cannot be found!" << "\n> ";
			// MessageBox(NULL, "Player Signature Cannot be found!", "Cheat", MB_OK);
		}
	}
	return 0;
}