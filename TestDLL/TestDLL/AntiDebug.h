#pragma once
#include <Windows.h>

BOOL NtGlobalFlagsDetection();
void PushPopStack();
BOOL NtGlobalFlag();
BOOL NtQueryInformationProcess_SystemKernel();