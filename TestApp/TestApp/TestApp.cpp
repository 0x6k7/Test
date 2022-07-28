#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <Lmcons.h>
#include "Base64.h"
#include "md5.h"
#include "obfuscate.h"

typedef void(*Func)();

namespace fs = std::filesystem;
using namespace std;

string getComputerName() {
	char computerName[UNLEN + 1];
	DWORD computerNameLength = UNLEN + 1;
	GetComputerName(computerName, &computerNameLength);
	return computerName;
}

int main()
{
	Func _Func;
	HINSTANCE hLibrary = LoadLibrary("TestDLL.dll");

	if (hLibrary) {
		_Func = (Func)GetProcAddress(hLibrary, "Protection");
		if (_Func) {
			_Func();
		}
	}

	else {
		cout << "Unable to load protection" << endl;
		cout << "Closing..." << endl;
	}

	FreeLibrary(hLibrary);

	char value[256];
	DWORD BufferSize = sizeof(value);
	LONG regGetValue = RegGetValueA(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), AY_OBFUSCATE("KEY"), RRF_RT_REG_SZ, NULL, value, &BufferSize);

	if (regGetValue != 0) {
		cout << AY_OBFUSCATE("Enter key: ") << endl;
		string key;
		cin >> key;

		if (key == "D9E6FD0C86E2426F90B22BF38AD29831" || key == "213") {
			if (!getComputerName) {
				cout << AY_OBFUSCATE("Computer name could have not been retrieved") << endl;
			}

			else {
				HKEY hkey;
				if (RegOpenKey(HKEY_CLASSES_ROOT, AY_OBFUSCATE("x-internet-signup"), &hkey) != ERROR_SUCCESS) {
					cout << AY_OBFUSCATE("Registry key could not have been opened") << endl;
				}

				else {
					if (RegSetValueEx(hkey, AY_OBFUSCATE("KEY"), 0, REG_SZ, (LPBYTE)"caf898115198eade1db61a34bae8efdd", strlen(AY_OBFUSCATE("caf898115198eade1db61a34bae8efdd")) * sizeof(char)) == ERROR_SUCCESS) {
						RegCloseKey(hkey);
					}
				}

				cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << endl;
			}
		}

		else {
			cout << AY_OBFUSCATE("Invalid key") << endl;
		}
	}

	else {
		if (regGetValue == 0) {
			cout << AY_OBFUSCATE("Welcome, ") << getComputerName() << endl;
		}
	}
	system("pause");
}
