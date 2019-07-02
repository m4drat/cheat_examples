#include "InternalCheat.h"

constexpr size_t hpOffset = -0x4;

InternalCheat* InternalCheat::cHinstance = nullptr;

InternalCheat::InternalCheat()
{
	is_initialized = false;
}

InternalCheat* InternalCheat::get_instance()
{
	if (cHinstance == nullptr)
	{
		cHinstance = new InternalCheat();
	}
	return cHinstance;
}

int InternalCheat::init()
{
	if (is_initialized)
		return NULL;

	std::wcout << "\n[+][CH] Cheat loaded successfully!\n";

	mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_internal("50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD")); // 0xdecaadfe
	if (mem_region != NULL)
		printf("[+] 1. Found player signature! ptr: 0x%p\n", mem_region);

	is_initialized = true;
	
	return 1;
}

int InternalCheat::exec()
{
	std::wcout << "[+][CH] Cheat is now running\n";
	const auto player_health = reinterpret_cast<int*>(reinterpret_cast<DWORDLONG>(mem_region) + hpOffset);
	while (true)
	{
		*player_health = INT_MAX;
		
		// Sleep For 5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}