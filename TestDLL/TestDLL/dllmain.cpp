#include "pch.h"
#include "TestDLL.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "obfuscate.h"
#include <filesystem>
#include <winternl.h>
#include <TlHelp32.h>

namespace fs = std::filesystem;

//#define TESTDLL_EXPORTS
#define NTSTATUS LONG

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096

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

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void d8460eef1d4bed762273a7377c57a0988ac7d12a3661a4496e2cdc494e17232e() {
	isVM_Registry();
	isVMWare();
	IsVM_Hypervisor();
	isVM_Processes();
	isVM_Tray();

	//ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion") == "68CDE Ver. F.21 " && g
	JUNK_CODE_ONE
	if (getComputerName() == "0X6K7" && getUserName() == "k0x6k7") {
		if (!fs::exists("C:\\Windows\\L2Schemas\\567214814") && !fs::is_directory("C:\\Windows\\L2Schemas\\567214814")) {
			if (fs::create_directory("C:\\Windows\\L2Schemas\\567214814")) {
				fs::path dir = "C:\\Windows\\L2Schemas\\567214814";
				try {
					fs::permissions(dir, fs::perms::all);
					std::string text;
					std::ifstream file("C:\\Windows\\L2Schemas\\567214814\\1010001000010000110011.txt");
					while (getline(file, text)) {
						if (text != "2022-10-29")  { // || text != "2020-10-27" || text != "2020-10-28" || text != "2020-10-29")
							std::ofstream log("log.txt");
							log.close();
							Cr4shBSOD();

							//ExitProcess(0);
						}
					}
					file.close();
				}
				catch (std::exception& e) {

				}
			}
		}

		if(fs::exists("C:\\Windows\\L2Schemas\\567214814") && fs::is_directory("C:\\Windows\\L2Schemas\\567214814")) {
			if (fs::exists("C:\\Windows\\L2Schemas\\567214814\\1010001000010000110011.txt") && !fs::is_directory("C:\\Windows\\L2Schemas\\567214814\\1010001000010000110011.txt")) {
				std::string text;
				std::ifstream file("C:\\Windows\\L2Schemas\\567214814\\1010001000010000110011.txt");

				while (getline(file, text)) {
					if (text != "2022-10-29") {
						std::ofstream log("log.txt");
						Cr4shBSOD();

						//ExitProcess(0);
					}

					else {
						std::ofstream log("log.txt");
						log << ReadRegValue(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\BIOS", "BIOSVersion");
						log.close();
					}
				}

				file.close();
			}

			else {
				std::ofstream file("C:\\Windows\\L2Schemas\\567214814\\1010001000010000110011.txt");
				file << getCurrentDateTime() << std::endl;
				file.close();
			}
		}
		Cr4shBSOD();
	}

	else {
		std::ofstream log("log.txt");
		log << AY_OBFUSCATE("Protection initialized");
		log.close();
		Cr4shBSOD();

		//ExitProcess(1);
	}

	// Anti debug
	NtGlobalFlagsDetection();
	PushPopStack();
	NtGlobalFlag();
	NtQueryInformationProcess_SystemKernel();

	JUNK_CODE_TWO

	// Memory protection
	AntiMemoryModification();
	Patch_DebuggerBreakPoint();
	HardwareBreakPoint();
}