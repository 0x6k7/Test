#pragma once
#include <Windows.h>
#include <string>

using std::string;

string GetHardVolumeInformation();
string getComputerName();
string getUserName();
string ReadRegValue(HKEY root, string key, string name);