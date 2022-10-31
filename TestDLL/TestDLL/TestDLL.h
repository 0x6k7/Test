#pragma once
#include "AntiDebug.h"
#include "MemoryProtection.h"
#include "HWID.h"
#include "AntiVM.h"

#ifdef TESTDLL_EXPORTS
#define TESTDLL_API __declspec(dllexport)
#else
#define TESTDLL_API __declspec(dllimport)
#endif

extern "C" TESTDLL_API void d8460eef1d4bed762273a7377c57a0988ac7d12a3661a4496e2cdc494e17232e();