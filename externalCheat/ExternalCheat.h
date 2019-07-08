#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <ctime>

#include "PatternScan.h"

class ExternalCheat
{
public:
	static ExternalCheat* get_instance();
	int init(DWORD pid);
	int exec();

	// RPM/WPM wrappers
	// Read a value from memory and put it in Value
	// Returns true on success, false on failure
	/*template <class T>
	static bool ReadMem(HANDLE psHandle, DWORDLONG dwAddress, T& Value)
	{
		return ReadProcessMemory(psHandle, reinterpret_cast<LPVOID>(dwAddress), Value, sizeof(T), NULL) == TRUE;
	}*/

	// Write a Value in memory
	// Returns true on success, false on failure
	template <class T>
	inline bool WriteMem(HANDLE psHandle, DWORDLONG dwAddress, const T& Value)
	{
		return WriteProcessMemory(psHandle, reinterpret_cast<LPVOID>(dwAddress), reinterpret_cast<void*>(Value), sizeof(T), NULL) == TRUE;
	}

private:
	HANDLE activePsHandle = NULL;
	static ExternalCheat* cHinstance;
	bool is_initialized = false;
	void* mem_region = nullptr;

	ExternalCheat();
};