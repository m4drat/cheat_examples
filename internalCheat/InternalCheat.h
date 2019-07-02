#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <ctime>

#include "PatternScan.h"

class InternalCheat
{
public:
	static InternalCheat* get_instance();
	int init();
	int exec();

	// RPM/WPM wrappers
	// Read a value from memory and put it in Value
	// Returns true on success, false on failure
	template <class T>
	inline bool ReadMem(DWORDLONG dwAddress, T& Value)
	{
		return ReadMemory(reinterpret_cast<LPVOID>(dwAddress), Value, sizeof(T), NULL) == TRUE;
	}

	// Write a Value in memory
	// Returns true on success, false on failure
	template <class T>
	inline bool WriteMem(DWORDLONG dwAddress, const T& Value)
	{
		return WriteMemory(reinterpret_cast<LPVOID>(dwAddress), Value, sizeof(T), NULL) == TRUE;
	}

private:
	static InternalCheat* cHinstance;
	bool is_initialized = false;
	void* mem_region = nullptr;

	InternalCheat();
};