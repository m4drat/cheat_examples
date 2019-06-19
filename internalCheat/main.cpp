#include "includes.h"

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason,_In_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		std::cout << "\nInjected!\n";
		MessageBox(nullptr, "Hello world!", "", 0);
	}
	return 0;
}