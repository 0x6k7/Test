#include <iostream>
#include <Windows.h>
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

	Func _Func;
	HINSTANCE hLibrary = LoadLibrary("TestDLL.dll");

	if (hLibrary) {
		std::cout << "Intializing protection...\n";
		Sleep(3000);
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

	JUNK_CODE_TWO

	FreeLibrary(hLibrary);
	system("cls");

	char value[256];
	DWORD BufferSize = sizeof(value);
	LONG regGetValue = RegGetValueA(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), AY_OBFUSCATE("9617fadb00a2ebf66d0d12f6d6b26ddfbbd2675b"), RRF_RT_REG_SZ, NULL, value, &BufferSize);

	if (regGetValue != 0) {
		std::cout << AY_OBFUSCATE("Enter key: ") << std::endl;
		std::string key;
		std::cin >> key;

		JUNK_CODE_ONE

		if (key == "D9E6FD0C86E2426F90B22BF38AD29831" || key == "213") {
			HKEY hkey;
			if (RegOpenKey(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), &hkey) != ERROR_SUCCESS) {
				std::cout << AY_OBFUSCATE("Registry key could not have been opened") << std::endl;
			}

			else {
				DWORD d;
				if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
					long setValue = RegSetValueEx(hkey, "9617fadb00a2ebf66d0d12f6d6b26ddfbbd2675b", 0, REG_SZ, (LPBYTE)"4f30e122dc11ad01425d5d0d854530cd356da3af", strlen("4f30e122dc11ad01425d5d0d854530cd356da3af") + 1);
					if (setValue == ERROR_SUCCESS) {
					}

					else {
						std::cout << "Could not initialize protection. Quitting...\n";
						ExitProcess(1);
					}
				}

				if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
					long setValue = RegSetValueEx(hkey, "aebbe9b71bd2addaea690953e419bf11b49ae91c", 0, REG_SZ, (LPBYTE)"4fbf4a66974fc07dad5162b9536e881d09474425", strlen("4fbf4a66974fc07dad5162b9536e881d09474425") + 1);
					if (setValue == ERROR_SUCCESS) {
					}

					else {
						std::cout << "Could not initialize protection. Quitting...\n";
						ExitProcess(1);
					}
				}

				if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
					long setValue = RegSetValueEx(hkey, "3b2f4dbf3337b0b98ec8ff6e2e154b02b8b7af17", 0, REG_SZ, (LPBYTE)"9adff33cd4045680f1282c74f59273b53b4736e5", strlen("9adff33cd4045680f1282c74f59273b53b4736e5") + 1);
					if (setValue == ERROR_SUCCESS) {
					}

					else {
						std::cout << "Could not initialize protection. Quitting...\n";
						ExitProcess(1);
					}
				}
			}

			std::cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << std::endl;
		}

		else {
			HKEY hkey;
			DWORD d;
			if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
				long setValue = RegSetValueEx(hkey, "6a36b2b37c433ab31476dc321b02979e5e44156a", 0, REG_SZ, (LPBYTE)"6a36b2b37c433ab31476dc321b02979e5e44156a", strlen("4f30e122dc11ad01425d5d0d854530cd356da3af") + 1);
				if (setValue == ERROR_SUCCESS) {
					
				}

				else {
					std::cout << "Could not initialize protection. Quitting...\n";
					ExitProcess(1);
				}
			}

			if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
				long setValue = RegSetValueEx(hkey, "164589a85a6aa4494f2a85592e861c28436462b4", 0, REG_SZ, (LPBYTE)"164589a85a6aa4494f2a85592e861c28436462b4", strlen("4f30e122dc11ad01425d5d0d854530cd356da3af") + 1);
				if (setValue == ERROR_SUCCESS) {
					
				}

				else {
					std::cout << "Could not initialize protection. Quitting...\n";
					ExitProcess(1);
				}
			}

			if (RegCreateKeyEx(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), 0, NULL, 0, KEY_WRITE, NULL, &hkey, &d) == ERROR_SUCCESS) {
				long setValue = RegSetValueEx(hkey, "c93c1fb68aa5e4e7e21cb74df7322fd7ce60359c", 0, REG_SZ, (LPBYTE)"c93c1fb68aa5e4e7e21cb74df7322fd7ce60359c", strlen("4f30e122dc11ad01425d5d0d854530cd356da3af") + 1);
				if (setValue == ERROR_SUCCESS) {
					
				}

				else {
					std::cout << "Could not initialize protection. Quitting...\n";
					ExitProcess(1);
				}
			}

			std::cout << AY_OBFUSCATE("Invalid key") << std::endl;
		}
	}

	else {
		if (regGetValue == 0)
			std::cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << std::endl;
	}
	system("pause");
}