#include <Windows.h>
#include "AntiDump.h"

void ErasePEHeaderFromMemory() {
	DWORD OldProtect = 0;
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &OldProtect);

	SecureZeroMemory(pBaseAddr, 4096);
}

void SizeOfImage() {
	__asm {
		mov eax, fs:[0x30]
		mov eax, [eax + 0x0c]
		mov eax, [eax + 0x0c]
		mov dword ptr[eax + 20h], 20000h
	}
}
