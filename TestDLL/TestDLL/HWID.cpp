#include <iostream>
#include <string>
#include <Windows.h>
#include <memory>
#include <iphlpapi.h>
#include "obfuscate.h"

//#pragma warning(disable : 4996)

using namespace std;

string GetHardVolumeInformation() {
	HANDLE h = CreateFile(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		return false;
	}

	unique_ptr<remove_pointer<HANDLE> ::type, void(*)(HANDLE)>
	hDevice{ h, [](HANDLE handle) {CloseHandle(handle); } };

	STORAGE_PROPERTY_QUERY SPQ;
	SPQ.PropertyId = StorageDeviceProperty;
	SPQ.QueryType = PropertyStandardQuery;

	STORAGE_DESCRIPTOR_HEADER SDH;
	DWORD bytesReturned = 0;

	if (!DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &SPQ, sizeof(SPQ), &SDH, sizeof(SDH), &bytesReturned, NULL)) {
		return false;
	}

	const DWORD outBufferSize = SDH.Size;
	unique_ptr<BYTE[]> outBuffer{ new BYTE[outBufferSize] {} };

	if (!DeviceIoControl(hDevice.get(), IOCTL_STORAGE_QUERY_PROPERTY, &SPQ, sizeof(SPQ), outBuffer.get(), outBufferSize, &bytesReturned, NULL)) {
		return false;
	}

	STORAGE_DEVICE_DESCRIPTOR* pDevice = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(outBuffer.get());
	const DWORD serialNumberOffset = pDevice->SerialNumberOffset;
	if (serialNumberOffset == 0) {
		return false;
	}

	const char* serialNumber = reinterpret_cast<const char*>(outBuffer.get() + serialNumberOffset);
	return serialNumber;
}

void GetGUID() {
	char value[256];
	DWORD BufferSize = sizeof(value);
	LONG regGetValue = RegGetValueA(HKEY_LOCAL_MACHINE, AY_OBFUSCATE("Microsoft\\Cryptography\\"), AY_OBFUSCATE("MachineGuid"), RRF_RT_REG_SZ, NULL, value, &BufferSize);

	cout << regGetValue << endl;
}

