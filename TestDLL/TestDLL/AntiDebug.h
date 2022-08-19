#pragma once
#include <Windows.h>
#include <string>

BOOL NtGlobalFlagsDetection();
void PushPopStack();
BOOL NtGlobalFlag();
BOOL NtQueryInformationProcess_SystemKernel();
std::string getCurrentDateTime();