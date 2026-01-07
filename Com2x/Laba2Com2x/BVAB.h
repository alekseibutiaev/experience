#pragma once
#include "IBVAB.h"

class BVAB : public IBVAB_power
{
protected:
   // Reference count
   long          m_lRef;

public:
	BVAB(void);
	~BVAB(void);

	//IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void  **ppv);
	virtual ULONG   STDMETHODCALLTYPE AddRef(void);
	virtual ULONG   STDMETHODCALLTYPE Release(void);  

	//IBVAB_power
	virtual HRESULT STDMETHODCALLTYPE Pow(const double x, const double y, double& z);    
	virtual HRESULT STDMETHODCALLTYPE Log(const double x, const double y, double& z);
};
