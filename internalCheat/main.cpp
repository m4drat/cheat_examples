#include <iostream>
#include <Windows.h>

#include "InternalCheat.h"

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		InternalCheat *cheat = InternalCheat::get_instance();
		cheat->init();
		cheat->exec();
	}
	return 0;
}