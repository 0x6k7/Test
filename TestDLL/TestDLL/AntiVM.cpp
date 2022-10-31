#include "pch.h"
#include <iostream>
#include "HWID.h"
#include <string>
#include <Windows.h>
#include "obfuscate.h"
#include "MemoryProtection.h"
#include <limits.h>
#include <intrin.h>
#include <TlHelp32.h>

using std::cout;

void isVM_Registry() {
	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemSKU") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "SystemProductName") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardProduct") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BaseBoardVersion") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVendor") == "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	if (ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\DSDT\\VBOX__\\VBOXBIOS", "") != "") {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}

	else {
		
	}
}

bool isVMWare() {
	bool res = true;

	__try
	{
		__asm
		{
			push   edx
			push   ecx
			push   ebx

			mov    eax, 'VMXh'
			mov    ebx, 0
			mov    ecx, 10
			mov    edx, 'VX' 

			in     eax, dx 
						   

						   cmp    ebx, 'VMXh' 
						   setz[res] 

						   pop    ebx
						   pop    ecx
						   pop    edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		res = false;
	}

	return res;
}

bool IsVM_Hypervisor() {
	int cpuInfo[4] = { };
	__cpuid(cpuInfo, 1);

	if (!(cpuInfo[2] && (1 << 31)))
		return false;

	const auto queryVendorId = 0x40000000;
	__cpuid(cpuInfo, queryVendorId);

	const int vendorIdLength = 13;
	using VendorIdStr = char[vendorIdLength];

	VendorIdStr hyperVendorId = {};
	memcpy(hyperVendorId + 0, &cpuInfo[1], 4);
	memcpy(hyperVendorId + 4, &cpuInfo[2], 4);
	memcpy(hyperVendorId + 8, &cpuInfo[3], 4);
	hyperVendorId[12] = '\0';

	static const VendorIdStr vendors[]{
		"KVMKVMKVM\0\0\0",
		"Microsoft Hv",
		"VMwareVMware",
		"XenVMMXenVMM",
		"prl hyperv  ",
		"VBoxVBoxVBox"
	};

	for (const auto& vendor : vendors) {
		if (!memcmp(vendor, hyperVendorId, vendorIdLength))
			return true;
	}

	Cr4shBSOD();
	return false;
}

int isVM_Processes() {
	int res = FALSE;
	HANDLE hSnap;
	PROCESSENTRY32 pEntry;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		pEntry.dwSize = sizeof(PROCESSENTRY32);
	}

	else {
		return FALSE;

		if (!Process32First(hSnap, &pEntry)) {
			CloseHandle(hSnap);
			return FALSE;
		}
	}

	do {
		if (lstrcmpi(pEntry.szExeFile, L"vboxservice.exe") == 0) {
			cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		}
		if (lstrcmpi(pEntry.szExeFile, L"vboxtray.exe") == 0) {
			cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		}
	} while (Process32Next(hSnap, &pEntry));
	return res;
}

int isVM_Tray() {
	HWND h1 = FindWindow(L"VboxTrayToolWndClass", NULL);
	HWND h2 = FindWindow(L"VboxTrayToolWnd", NULL);

	if (h1 || h2) {
		cout << AY_OBFUSCATE("A VM has been detected. Quitting...\n");
		Cr4shBSOD();
	}
	else
		return FALSE;
}