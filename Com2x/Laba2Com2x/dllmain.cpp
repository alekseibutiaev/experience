// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

extern HMODULE hBVAA;
extern HMODULE hBVAB;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
							hBVAA = hModule;
							hBVAB = hModule;
							break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

