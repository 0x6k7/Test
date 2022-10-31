#include <iostream>
#include <string>
#include <Windows.h>
#include <memory>
#include "obfuscate.h"
#include <array>
#include <cstdio>

#pragma comment(lib, "user32.lib")

using std::string;
using std::unique_ptr;
using std::remove_pointer;
using std::wcout;
using std::cout;
using std::endl;
using std::array;
using std::shared_ptr;

#define INFO_BUFFER_SIZE 32767

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

string ReadRegValue(HKEY root, string key, string name)
{
	HKEY hKey;
	if (RegOpenKeyExA(root, key.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		wcout << AY_OBFUSCATE("Could not open registry key\n");

	DWORD type;
	DWORD cbData;
	if (RegQueryValueExA(hKey, name.c_str(), NULL, &type, NULL, &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		cout << AY_OBFUSCATE("Could not read registry value\n");
	}

	if (type != REG_SZ) {
		RegCloseKey(hKey);
		cout << AY_OBFUSCATE("Incorrect registry value type\n");
	}

	string value(cbData / sizeof(char), L'\0');
	if (RegQueryValueExA(hKey, name.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS) {
		RegCloseKey(hKey);
		cout << AY_OBFUSCATE("Could not read registry value");
	}

	RegCloseKey(hKey);

	return value;
}

string getComputerName() {
	CHAR infoBuffer[INFO_BUFFER_SIZE];
	DWORD bufferCharCount = INFO_BUFFER_SIZE;

	bufferCharCount = INFO_BUFFER_SIZE;
	if (!GetComputerNameA(infoBuffer, &bufferCharCount))
		cout << AY_OBFUSCATE("Computer name could not be retrieved") << endl;

	return infoBuffer;
}

string getUserName() {
	CHAR infoBuffer[INFO_BUFFER_SIZE];
	DWORD bufferCharCount = INFO_BUFFER_SIZE;

	bufferCharCount = INFO_BUFFER_SIZE;
	if (!GetUserNameA(infoBuffer, &bufferCharCount))
		cout << AY_OBFUSCATE("User name could not be retrieved") << endl;

	return infoBuffer;
}