#pragma once
#include "AntiDebug.h"
#include "AntiAnalyze.h"
#include "MemoryProtection.h"
#include "HWID.h"

#ifdef TESTDLL_EXPORTS
#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)
#endif

extern "C" TESTDLL_API void Protection();