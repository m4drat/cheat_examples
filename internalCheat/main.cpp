#include "includes.h"

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		MessageBox(nullptr, "Cheat Injected Successfully!", "", 0);
	}
	return 0;
}