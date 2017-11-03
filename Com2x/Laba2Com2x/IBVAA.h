#pragma once
#include <ObjBase.h>

// {5219B44A-0874-449E-8611-B7080DBFA6AB}
static const GUID IID_IBVAA_summer =
{0x5219b44a, 0x874, 0x449e, { 0x86, 0x11, 0xb7, 0x8, 0xd, 0xbf, 0xa6, 0xab} };


interface IBVAA_summer:IUnknown // сумматор
{
 virtual HRESULT  __stdcall Add(
	 const double x,   // [in]слагаемое x 
	 const double y,   // [in]слагаемое y
	 double& z         // [out] результат z = x+y
	 ) = 0;   
 virtual HRESULT  __stdcall Sub(
	 const double x,   // [in] 
	 const double y,   // [in] вычитаемое y
	 double& z        // [out] результат z = x-y
	 ) = 0;   
};

// {8A2A00DD-8B8D-4898-B08E-000A6E40A2B5}
static const GUID IID_IBVAA_multiplier = 
{ 0x8a2a00dd, 0x8b8d, 0x4898, { 0xb0, 0x8e, 0x0, 0xa, 0x6e, 0x40, 0xa2, 0xb5 } };

interface IBVAA_multiplier:IUnknown // множитель
{
 virtual HRESULT  __stdcall Mul(
	 const double x,   // [in]сомножитель x
	 const double y,   // [in]сомножитель y
	 double& z         // [out] результат z = x*y
	 ) = 0;   
 virtual HRESULT  __stdcall Div(
	 const double x,   // [in] делимое x
	 const double y,   // [in] делитель y
	 double& z         // [out] результат z = x/y
	 ) = 0;   
};
