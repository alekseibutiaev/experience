#pragma once
#include "IBVAA.h"


class BVAA : public IBVAA_summer, public IBVAA_multiplier
{
protected:
   // Reference count
	// Переменная-член класса добавлена для подсчета
   // обращений извне к интерфейсу объекта
   long          m_lRef;

public:
	BVAA(void);
	~BVAA(void);

	//IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void  **ppv);
	//Метод QueryInterface обращается к идентификатору интерфейса (Interface Identifier — IID), 
	//и возвращает указатель на определенный интерфейс (например, IUnknown, IBVAA_summer)

	//Управление временем жизни компонента:
	virtual ULONG   STDMETHODCALLTYPE AddRef(void); //Увеличение кол-ва обращений к объекту (когда 0 - объек удаляет себя)
	virtual ULONG   STDMETHODCALLTYPE Release(void);

	//Реализация интерфейсов:
	//IBVAA_summer
	virtual HRESULT STDMETHODCALLTYPE Add(const double x, const double y, double& z);
	virtual HRESULT STDMETHODCALLTYPE Sub(const double x, const double y, double& z); 

	//IBVAA_multiplier
	virtual HRESULT STDMETHODCALLTYPE Mul(const double x, const double y, double& z);
	virtual HRESULT STDMETHODCALLTYPE Div(const double x, const double y, double& z);   
};

