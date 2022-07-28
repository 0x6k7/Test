#include "pch.h"
#include "AntiDump.h"

void ErasePEHeaderFromMemory() {
	DWORD Protect = 0;
	char *pBaseAddress = (char*)GetModuleHandle(NULL);
	VirtualProtect(pBaseAddress, 4096, PAGE_READWRITE, &Protect);
	SecureZeroMemory(pBaseAddress, 4096);
}

void SizeOfImage() {
	__asm
	{
		mov eax, fs:[0x30]
		mov eax, [eax + 0x0c]
		mov eax, [eax + 0x0c]
		mov dword ptr [eax+20h], 20000h
	}
}