#include <Windows.h>
#include <intrin.h>
#include <TlHelp32.h>
#include <winternl.h>

#pragma intrinsic(_ReturnAddress)

#define SHUTDOWN_PRIV 19
#pragma comment(lib, "ntdll.lib")

using namespace std;

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enabled, BOOLEAN CurrentThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStat, ULONG NumberOfParametrs, ULONG UnicodeStringParametrMask, PULONG_PTR Parametrs, ULONG Response, PULONG Response2);

int Cr4shBSOD() {
	BOOLEAN isAdmin = FALSE;
	ULONG ErrorResponse = 0;
	RtlAdjustPrivilege(SHUTDOWN_PRIV, TRUE, FALSE, &isAdmin);
	NtRaiseHardError(STATUS_ACCESS_VIOLATION, 0, 0, NULL, 6, &ErrorResponse);
	return 0;
}

void AntiMemoryModification() {
	PVOID pRetAddress = _ReturnAddress();
	BYTE byte;

	if (FALSE != Toolhelp32ReadProcessMemory(GetCurrentProcessId(), _ReturnAddress(), &byte, sizeof(BYTE), NULL)) {
		if (byte == 0xCC)
			//ExitProcess(0);
			Cr4shBSOD();
	}
}

void Patch_DebuggerBreakPoint() {
	HMODULE hNtDLL = GetModuleHandleA("ntdll.dll");
	if (!hNtDLL) return;

	FARPROC pDbgBreakPoint = GetProcAddress(hNtDLL, "DbgBreakPoint");
	if (!pDbgBreakPoint) return;

	DWORD oldProtect;
	if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		return;
	}

	*(PBYTE)pDbgBreakPoint = (BYTE)0xC3;
}

bool HardwareBreakPoint() {
	CONTEXT context;
	SecureZeroMemory(&context, sizeof(CONTEXT));
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;

	if (!GetThreadContext(GetCurrentThread(), &context))
		return false;

	return context.Dr0 || context.Dr1 || context.Dr2 || context.Dr3;
}