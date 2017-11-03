#include "StdAfx.h"
#include "BVAA.h"

extern  ULONG g_Components;    // количество компонент; 

BVAA::BVAA(void) : m_lRef (1) {
	InterlockedIncrement((LONG*)&g_Components);
}


BVAA::~BVAA(void) {
	InterlockedDecrement((LONG*)&g_Components);
}

//IUnknown
HRESULT STDMETHODCALLTYPE BVAA::QueryInterface(REFIID riid, void  **ppv) {
	HRESULT rc = S_OK;                                    // COM
	*ppv = NULL;                                          // COM                       
	if       (riid == IID_IUnknown) *ppv = (IBVAA_summer*)this; 
	else if  (riid == IID_IBVAA_summer)      *ppv = (IBVAA_summer*)this;
	else if  (riid == IID_IBVAA_multiplier)      *ppv = (IBVAA_multiplier*)this;
	else rc = E_NOINTERFACE;                             // COM   	
	if (rc == S_OK) this->AddRef();
	//LOG("CA::QueryInterface rc = ",rc);
    return rc;
}

ULONG STDMETHODCALLTYPE BVAA::AddRef(void) {
	InterlockedIncrement ((LONG*)&(this->m_lRef));

	return this->m_lRef;
}

ULONG STDMETHODCALLTYPE BVAA::Release(void) {
	InterlockedDecrement ((LONG*)&(this->m_lRef));

	// когда значение счетчика обращений
	// становится равным нулю, объект удаляет сам себя
	if ( m_lRef == 0 ) {
		delete this;
		// нельзя вернуть m_lRef, поскольку его уже не существует
		return 0;
	}
	else
		return m_lRef;
	//LOG("CA::AddRef rc = ",this->m_Ref);
	// LogCOM<<"CA::AddRef rc = "<<this->m_Ref<<std::endl;
	//return this->m_lRef;
}

//IBVAA_summer
HRESULT STDMETHODCALLTYPE BVAA::Add(const double x, const double y, double& z) {
	z = x + y;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE BVAA::Sub(const double x, const double y, double& z) {
	z = x - y;
	return S_OK;
}

//IBVAA_multiplier
HRESULT STDMETHODCALLTYPE BVAA::Mul(const double x, const double y, double& z) {
	z = x * y;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE BVAA::Div(const double x, const double y, double& z) {
	z = x / y;
	return S_OK;
}