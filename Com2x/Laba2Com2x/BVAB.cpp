#include "StdAfx.h"
#include "BVAB.h"
#include "math.h"

extern  ULONG g_Components;    // количество компонент; 

BVAB::BVAB(void) : m_lRef (1) {
	InterlockedIncrement((LONG*)&g_Components);
}


BVAB::~BVAB(void) {
	InterlockedDecrement((LONG*)&g_Components);
}

//IUnknown
HRESULT STDMETHODCALLTYPE BVAB::QueryInterface(REFIID riid,void  **ppv) {
	HRESULT rc = S_OK;
	*ppv = NULL;                                          // COM                       
	if       (riid == IID_IUnknown) *ppv = (IBVAB_power*)this; 
	else if  (riid == IID_IBVAB_power)      *ppv = (IBVAB_power*)this;
	else rc = E_NOINTERFACE;                             // COM   	
	if (rc == S_OK) this->AddRef();

    return rc;
}

ULONG   STDMETHODCALLTYPE BVAB::AddRef(void) {
	InterlockedIncrement(&m_lRef);
	return this->m_lRef;
}

ULONG   STDMETHODCALLTYPE BVAB::Release(void) {
	InterlockedDecrement(&m_lRef);
	if (this->m_lRef == 0) {
		delete this;
		return 0;
	}
	else
	return this->m_lRef;
}

//IBVAB_multiplier
HRESULT STDMETHODCALLTYPE BVAB::Pow(const double x, const double y, double& z) {
	z = pow(x, y);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE BVAB::Log(const double x, const double y, double& z) {
	z = log(x) / log(y);
	return S_OK;
}