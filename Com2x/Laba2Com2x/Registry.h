#pragma once
#include <ObjBase.h>

HMODULE hBVAA;
HMODULE hBVAB;

// {6942E971-6F95-44BC-B3A9-EFD270EB39C9}
GUID CLSID_BVAA = 
{ 0x6942e971, 0x6f95, 0x44bc, { 0xb3, 0xa9, 0xef, 0xd2, 0x70, 0xeb, 0x39, 0xc9} };

// {01ADBE7E-4EE3-4F36-9DCA-95722F897AE1}
GUID CLSID_BVAB =  
{ 0x1adbe7e, 0x4ee3, 0x4f36, { 0x9d, 0xca, 0x95, 0x72, 0x2f, 0x89, 0x7a, 0xe1} };


const WCHAR FName[]  = L"BVA COM";
const WCHAR VerInd[] = L"BVAA.Component";
const WCHAR ProgId[] = L"BVAA.Component.1";

const WCHAR FName2[]  = L"BVA COM2";
const WCHAR VerInd2[] = L"BVAB.Component";
const WCHAR ProgId2[] = L"BVAB.Component.2";
//extern "C"  __declspec(dllexport) HRESULT DllInstall(char* s);
//extern "C"  __declspec(dllexport) HRESULT DllRegisterServer();
//extern "C"  __declspec(dllexport) HRESULT DllUnregisterServer();
STDAPI DllInstall(char* s);
STDAPI DllRegisterServer();
STDAPI DllUnregisterServer();
// This function will register a component in the Registry.
// The component calls this function from its DllRegisterServer function.
HRESULT RegisterServer(HMODULE hModule, 
                       const CLSID& clsid, 
                       const WCHAR* szFriendlyName,
                       const WCHAR* szVerIndProgID,
                       const WCHAR* szProgID) ;

// This function will unregister a component.  Components
// call this function from their DllUnregisterServer function.
HRESULT UnregisterServer(const CLSID& clsid,
                         const WCHAR* szVerIndProgID,
                         const WCHAR*  szProgID) ;