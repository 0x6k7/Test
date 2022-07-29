#include <Windows.h>
#include <intrin.h>
#include <TlHelp32.h>
#pragma intrinsic(_ReturnAddress)

using namespace std;

void AntiMemoryModification() {
	PVOID pRetAddress = _ReturnAddress();
	BYTE byte;

	if (FALSE != Toolhelp32ReadProcessMemory(GetCurrentProcessId(), _ReturnAddress(), &byte, sizeof(BYTE), NULL)) {
		if (byte == 0xCC)
			ExitProcess(0);
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