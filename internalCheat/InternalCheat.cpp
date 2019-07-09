#include "InternalCheat.h"

constexpr long long int hpOffset = -0x4;

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

	mem_region = reinterpret_cast<void*>(PatternScan::find_pattern_internal("50 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FD FD FD FD"));
	if (mem_region != NULL)
		printf("[+][CH] Found player signature! ptr: 0x%p\n", mem_region);
	else
	{
		printf("[-][CH] Cannot find player signature! Aborting.\n> ");
		return NULL;
	}

	is_initialized = true;
	
	return 1;
}

int InternalCheat::exec()
{
	std::wcout << "[+][CH] Cheat is now running\n> ";
	const auto player_health = reinterpret_cast<int*>(reinterpret_cast<DWORDLONG>(mem_region) + hpOffset);
	while (true)
	{
		*player_health = INT_MAX;

		// Sleep For 5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}