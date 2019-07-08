#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

std::vector<DWORD> get_pid_by_name(std::wstring targetName);