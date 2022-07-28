#include <iostream>
#include <string>
#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>

using namespace std;

string GetHardVolumeInformation() {
	UCHAR szFileSys[255], szVolumeBuff[255];
	DWORD dwSerial;
	DWORD dwMFL;
	DWORD dwSysFlags;

	int error = 0;
	bool getHDD = GetVolumeInformation(LPCTSTR("C://"), (LPTSTR)szVolumeBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

	if (!getHDD) {
		cout << "Could not retrieve hark disk serial number. Quitting..." << endl;
		system("pause");
	}

	return std::to_string(getHDD).c_str();
}

