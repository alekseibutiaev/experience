// Laba2Com2x.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ClassFactory.h"
#include "BVAA.h"
#include "BVAB.h"
//#include "Registry.h"

ULONG g_ServerLocks = 0;    // блокировки сервера; 
ULONG g_Components  = 0;    // количество компонент; 

extern  GUID CLSID_BVAA;
extern  GUID CLSID_BVAB;

//В зависимости от варианта хранения используется одна из двух основных технологий доступа.
//DLL-файлы должны предоставлять в общее пользование две функции: DllGetClassObject и DllCanUnloadNow,
//a исполняемые файлы должны регистрировать свои фабрики классов с помощью функции CoRegisterClassObject из библиотеки СОМ API.

STDAPI DllCanUnloadNow() {
	//SEQ;
	HRESULT rc = E_UNEXPECTED;
	if ((g_ServerLocks == 0)&&(g_Components  == 0)) rc = S_OK;
	else rc = S_FALSE;
	//LOG("DllCanUnloadNow: rc =",rc);
	//LogCOM<<"DllCanUnloadNow: rc = "<<rc<<std::endl;
	return rc;
};
STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void**ppv) {
	//SEQ;
	HRESULT rc = E_UNEXPECTED;

	if (clsid == CLSID_BVAA) {
		ClassFactory<BVAA> *cf = new ClassFactory<BVAA>();
		rc = cf->QueryInterface(iid, ppv);
		cf->Release();
	} 
	else
	if (clsid == CLSID_BVAB) {
		ClassFactory<BVAB> *cf = new ClassFactory<BVAB>();
		rc = cf->QueryInterface(iid, ppv);
		cf->Release();
	}
	else  
		rc = CLASS_E_CLASSNOTAVAILABLE;

	return rc;
};