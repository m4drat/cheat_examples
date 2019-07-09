#include "ExternalCheat.h"

constexpr long long int hpOffset = -0x4;

ExternalCheat* ExternalCheat::cHinstance = nullptr;

ExternalCheat::ExternalCheat()
{
	is_initialized = false;
}

ExternalCheat* ExternalCheat::get_instance()
{
	if (cHinstance == nullptr)
	{
		cHinstance = new ExternalCheat();
	}
	return cHinstance;
}

int ExternalCheat::init(DWORD pid)
{
	if (is_initialized)
		return NULL;

	// Open handle to process with full access
	activePsHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

	if (activePsHandle != nullptr)
	{
		mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_external(activePsHandle, "50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
		if (mem_region != NULL)
		{
			printf("[+] Found player signature! ptr: 0x%p\n", mem_region);
		} 
		else {
			printf("[-] Cannot find player signature! Aborting.\n");
			return NULL;
		}

		is_initialized = true;
		return 1;
	}
	else {
		std::wcout << "[-] Cannot open process.\n";
		std::wcout << "[-] Check your privilegies.\n";
		getchar();
		return NULL;
	}
}

int ExternalCheat::exec()
{
	std::wcout << "[+][CH] Cheat is now running\n";
	while (true)
	{
		int newHp = INT_MAX;
		if (!WriteMem(activePsHandle, reinterpret_cast<DWORDLONG>(mem_region) + hpOffset, &newHp))
		{
			std::wcout << "[-] Cannot write process memory!\n";
		}

		// Sleep For 5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}