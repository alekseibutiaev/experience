// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObjBase.h"
#include "COM.h"
#include "../Laba2Com2x/IBVAA.h"
#include "../Laba2Com2x/IBVAB.h"

int _tmain(int argc, _TCHAR* argv[])
{
	double zA = 0, zS = 0, zM = 0, zD = 0, zP = 0, zL = 0;
	CoInitialize(NULL);
 
	IBVAA_summer* ps = NULL;
	HRESULT hrA = CoCreateInstance(CLSID_BVAA, NULL, CLSCTX_INPROC_SERVER, IID_IBVAA_summer, (void**)&ps );
	
	if (SUCCEEDED(hrA)) {
		ps->Add(2,3,zA); printf("ps->Add(2,3,zA) = %4f \n", zA);
		ps->Sub(16,5, zS); printf("ps->Sub(16,5, zS) = %4f \n", zS);
		//ps->Release(); 
	};

	IBVAA_multiplier* pm = NULL;
	HRESULT hrA_m = ps->QueryInterface(IID_IBVAA_multiplier, (void**)&pm);
	
	if (SUCCEEDED(hrA_m)) {
		pm->Mul(3,6, zM); printf("pm->Mul(3,6, zM) = %4f \n", zM);
		pm->Div(16,4, zD); printf("pm->Div(16,4, zD) = %4f \n", zD);
		pm->Release();
	};
	ps->Release();

	IBVAB_power* pp = NULL;
	
	HRESULT hrB  = CoCreateInstance(CLSID_BVAB, NULL, CLSCTX_INPROC_SERVER, IID_IBVAB_power, (void**)&pp );

	if (SUCCEEDED(hrB)) {
		pp->Pow(2,3,zP);  printf("pp->Pow(2,3,zP) = %4f \n", zP);
		pp->Log(16,2, zL);   printf("pp->Log(16,2, zL) = %4f \n", zL);
		pp->Release();
	};
	
	CoFreeUnusedLibraries();

	return 0;
}

