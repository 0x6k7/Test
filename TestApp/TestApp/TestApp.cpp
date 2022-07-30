#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <Lmcons.h>
#include "Base64.h"
#include "AntiDump.h"
#include "md5.h"
#include "obfuscate.h"

#define INFO_BUFFER_SIZE 32767

#define JUNK_CODE_ONE        \
    __asm{push eax}            \
    __asm{xor eax, eax}        \
    __asm{setpo al}            \
    __asm{push edx}            \
    __asm{xor edx, eax}        \
    __asm{sal edx, 2}        \
    __asm{xchg eax, edx}    \
    __asm{pop edx}            \
    __asm{or eax, ecx}        \
    __asm{pop eax}

#define JUNK_CODE_TWO \
__asm{push eax} \
 __asm{xor eax, eax} \
__asm{mov eax,12} \
__asm{pop eax}

typedef void(*Func)();

namespace fs = std::filesystem;

std::string getComputerName() {
	CHAR infoBuffer[INFO_BUFFER_SIZE];
	DWORD bufferCharCount = INFO_BUFFER_SIZE;

	bufferCharCount = INFO_BUFFER_SIZE;
	if (!GetComputerNameA(infoBuffer, &bufferCharCount))
		std::cout << AY_OBFUSCATE("Computer name could not have been retrieved") << std::endl;

	return infoBuffer;
}

int main()
{
	ErasePEHeaderFromMemory();
	SizeOfImage();

	JUNK_CODE_TWO

	Func _Func;
	HINSTANCE hLibrary = LoadLibrary("TestDLL.dll");

	if (hLibrary) {
		_Func = (Func)GetProcAddress(hLibrary, "Protection");
		if (_Func) {
			_Func();
		}
	}

	else {
		std::cout << AY_OBFUSCATE("Unable to load protection") << std::endl;
		std::cout << AY_OBFUSCATE("Closing...") << std::endl;
		ExitProcess(1);
	}

	FreeLibrary(hLibrary);

	JUNK_CODE_ONE

	char value[256];
	DWORD BufferSize = sizeof(value);
	LONG regGetValue = RegGetValueA(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), AY_OBFUSCATE("KEY"), RRF_RT_REG_SZ, NULL, value, &BufferSize);

	if (regGetValue != 0) {
		std::cout << AY_OBFUSCATE("Enter key: ") << std::endl;
		std::string key;
		std::cin >> key;

		JUNK_CODE_TWO

		if (key == "D9E6FD0C86E2426F90B22BF38AD29831") {
			HKEY hkey;
			if (RegOpenKey(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), &hkey) != ERROR_SUCCESS) {
				std::cout << AY_OBFUSCATE("Registry key could not have been opened") << std::endl;
			}

			else {
				if (RegSetValueEx(hkey, AY_OBFUSCATE("KEY"), 0, REG_SZ, (LPBYTE)"caf898115198eade1db61a34bae8efdd", strlen(AY_OBFUSCATE("caf898115198eade1db61a34bae8efdd")) * sizeof(char)) == ERROR_SUCCESS) {
					RegCloseKey(hkey);
				}
			}

			std::cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << std::endl;
		}

		else {
			std::cout << AY_OBFUSCATE("Invalid key") << std::endl;
		}
	}

	else {
		JUNK_CODE_ONE

		if (regGetValue == 0)
			std::cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << std::endl;
	}
	system("pause");
}