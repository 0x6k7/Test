#include "pch.h"
#include "AntiDebug.h"
#include <Windows.h>
#include <string>
#include <time.h>
#include <WinUser.h>

#define NTSTATUS LONG

BOOL NtGlobalFlagsDetection() {
	unsigned long NtGlobalFlags = 0;
	__asm
	{
		mov eax, fs:[30h]
		mov eax, [eax + 68h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70) {
		return true;
	}

	else {
		return false;
	}
}

void PushPopStack() {
	__asm {
		push ss
		pop ss
		mov eax, 9
		xor edx, edx
	}
}

BOOL NtGlobalFlag() {
	unsigned long NtGlobalFlags = 0;
	__asm {
		mov eax, fs:[30h]
		mov eax, [eax + 60h]
		mov NtGlobalFlags, eax
	}

	if (NtGlobalFlags & 0x70)
		return TRUE;
	else
		return FALSE;
}

BOOL NtQueryInformationProcess_SystemKernel() {
	typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
		BOOLEAN DebuggerEnabled;
		BOOLEAN DebuggerNotPresent;
	} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;
	SYSTEM_KERNEL_DEBUGGER_INFORMATION Info;

	enum SYSTEM_INFORMATION_CLASS { SystemKernelDebuggerInformation = 35 };

	typedef NTSTATUS(WINAPI *pZwQuerySystemInformation)(IN SYSTEM_INFORMATION_CLASS SystemInformationClass, IN OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength);

	pZwQuerySystemInformation ZwQuerySystemInformation = NULL;

#define STATUS_SUCCESS   ((NTSTATUS)0x00000000L) 
	HANDLE hProcess = GetCurrentProcess();

	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	if (hNtDll == NULL)
	{

	}

	ZwQuerySystemInformation = (pZwQuerySystemInformation)GetProcAddress(hNtDll, "ZwQuerySystemInformation");

	if (ZwQuerySystemInformation == NULL)
	{

	}

	if (STATUS_SUCCESS == ZwQuerySystemInformation(SystemKernelDebuggerInformation, &Info, sizeof(Info), NULL)) {
		if (Info.DebuggerEnabled)
		{
			if (Info.DebuggerNotPresent)
				return FALSE;
			else
				return TRUE;
		}
	}
}

std::string getCurrentDateTime() {
	time_t now = time(0);
	struct tm tStruct;
	char buffer[80];
	tStruct = *localtime(&now);

	localtime(&now);
	strftime(buffer, sizeof(buffer), "%F", &tStruct);

	return buffer;
}