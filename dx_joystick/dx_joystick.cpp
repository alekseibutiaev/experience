// dx_joystick.cpp : Defines the entry point for the console application.
//

// http://www.cs.cmu.edu/~jparise/directx/joystick/


#include "stdafx.h"

#include <dinput.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>


LPDIRECTINPUT8 di;

std::vector< LPDIRECTINPUTDEVICE8 > joysticks;

BOOL CALLBACK enumCallback( const DIDEVICEINSTANCE* instance, VOID* context ) {
  // Obtain an interface to the enumerated joystick.
  // If it failed, then we can't use this joystick. (Maybe the user unplugged
  // it while we were in the middle of enumerating it.)
  // Stop enumeration. Note: we're just taking the first joystick we get. You
  // could store all the enumerated joysticks and let the user pick.

  LPDIRECTINPUTDEVICE8 joystick;
  if( S_OK == di->CreateDevice(instance->guidInstance, &joystick, NULL ) ) {
    joysticks.push_back( joystick );
    return DIENUM_CONTINUE;
  }
  return DIENUM_STOP;
/*
  return DIENUM_CONTINUE;

  return S_OK != di->CreateDevice(instance->guidInstance, &joystick, NULL ) ? DIENUM_CONTINUE : DIENUM_STOP;
*/
}

BOOL CALLBACK enumAxesCallback( const DIDEVICEOBJECTINSTANCE* instance, VOID* context ) {
  LPDIRECTINPUTDEVICE8 joystick = ( LPDIRECTINPUTDEVICE8 )context;

  DIPROPRANGE propRange; 
  propRange.diph.dwSize       = sizeof(DIPROPRANGE); 
  propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
  propRange.diph.dwHow        = DIPH_BYID; 
  propRange.diph.dwObj        = instance->dwType;
  propRange.lMin              = -512; 
  propRange.lMax              = +511; 
    
  // Set the range for the axis
  if( S_OK != joystick->SetProperty(DIPROP_RANGE, &propRange.diph ) )
    return DIENUM_STOP;

  return DIENUM_CONTINUE;
}

HRESULT Poll( DIJOYSTATE2* js, LPDIRECTINPUTDEVICE8 f_joystick ) {
  HRESULT hr;
  if( DI_OK != ( hr = f_joystick->Poll() ) ) {
    // DInput is telling us that the input stream has been
    // interrupted. We aren't tracking any state between polls, so
    // we don't have any special reset that needs to be done. We
    // just re-acquire and try again.
    hr = f_joystick->Acquire();
    while( DIERR_INPUTLOST == hr )
      hr = f_joystick->Acquire();
    // If we encounter a fatal error, return failure.
    if( DIERR_INVALIDPARAM == hr || DIERR_NOTINITIALIZED == hr )
        return E_FAIL;
    // If another application has control of this device, return successfully.
    // We'll just have to wait our turn to use the joystick.
    if( DIERR_OTHERAPPHASPRIO == hr )
      return S_OK;
  }
  // Get the input's device state
  if(  S_OK != ( hr = f_joystick->GetDeviceState( sizeof( DIJOYSTATE2 ), js ) ) )
      // The device should have been acquired during the Poll()
    return hr;
  return S_OK;
}

class joystic_action {
public:
  joystic_action( HRESULT& f_result ) : pt_result( f_result ) {
  }
  virtual ~joystic_action(){}
  virtual bool operator()( LPDIRECTINPUTDEVICE8 f_joystick ) = 0;
protected:
  HRESULT& pt_result;
};

class set_format_data : public joystic_action {
public:
  set_format_data( HRESULT& f_result ) : joystic_action( f_result ) {
  }
  bool operator()( LPDIRECTINPUTDEVICE8 f_joystick ) {
    pt_result = f_joystick->SetDataFormat( &c_dfDIJoystick2 );
    return S_OK != pt_result;
  }
};

class get_capabilities {
public:
  get_capabilities( HRESULT& f_result ) : pv_result( f_result ) {
  }
  bool operator()( LPDIRECTINPUTDEVICE8 f_joystick, DIDEVCAPS& f_capabilities ) {
    f_capabilities.dwSize = sizeof(DIDEVCAPS);
    pv_result = f_joystick->GetCapabilities( &f_capabilities );
    return S_OK == pv_result;
  }
private:
  HRESULT& pv_result;
};

class enum_objects : public joystic_action {
public:
  enum_objects( HRESULT& f_result ) : joystic_action( f_result ) {
  }
  bool operator()( LPDIRECTINPUTDEVICE8 f_joystick ) {
    pt_result = f_joystick->EnumObjects( enumAxesCallback, f_joystick, DIDFT_AXIS );
    return S_OK != pt_result;
  }
};


int _tmain(int argc, _TCHAR* argv[]) {

  HRESULT hr;
  std::vector< LPDIRECTINPUTDEVICE8 >::iterator it;

  HMODULE mh = GetModuleHandle(NULL);

  // Create a DirectInput device
  if( S_OK != ( hr = DirectInput8Create( mh, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, 0 ) ) )
    return hr;
  // Look for the first simple joystick we can find.
  if( S_OK != ( hr = di->EnumDevices( DI8DEVCLASS_GAMECTRL, enumCallback, NULL, DIEDFL_ATTACHEDONLY ) ) )
    return hr;
  // Make sure we got a joystick
  if( joysticks.empty() ) {
    printf("Joystick not found.\n");
    return E_FAIL;
  }
  // Set the data format to "simple joystick" - a predefined data format 
  //
  // A data format specifies which controls on a device we are interested in,
  // and how they should be reported. This tells DInput that we will be
  // passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
  if( joysticks.end() != std::find_if( joysticks.begin(), joysticks.end(), set_format_data( hr ) ) )
     return hr;
#if 0
  // Set the cooperative level to let DInput know how this device should
  // interact with the system and with other DInput applications.
  if( S_OK != ( hr = joystick->SetCooperativeLevel( NULL, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
      return hr;
#endif
  // Determine how many axis the joystick has (so we don't error out setting
  // properties for unavailable axis)
  std::vector< DIDEVCAPS > capabilities( joysticks.size() );
  if( !std::equal( joysticks.begin(), joysticks.end(), capabilities.begin(), get_capabilities( hr ) ) )
    return hr;

  // Enumerate the axes of the joyctick and set the range of each axis. Note:
  // we could just use the defaults, but we're just trying to show an example
  // of enumerating device objects (axes, buttons, etc.).
  if( joysticks.end() != std::find_if( joysticks.begin(), joysticks.end(), enum_objects( hr ) ) )
    return hr;

  DIJOYSTATE2 js;

  for(;;) {
    std::vector< DIDEVCAPS >::iterator c;
    std::vector< LPDIRECTINPUTDEVICE8 >::iterator i;
    for( i = joysticks.begin(), c = capabilities.begin(); i != joysticks.end(); ++i, ++c ) {
      if( S_OK != Poll( &js, *i ) )
        break;
      std::cout << js.lX << " " << js.lY << " " << js.lZ << " ";
      std::transform( &js.rgbButtons[ 0 ], &js.rgbButtons[ c->dwButtons ],
        std::ostream_iterator< char >( std::cout, " " ), []( const unsigned char& f_value ){
          return 0 == f_value ? '0' : '1'; } );
      std::cout << " ";
    }
    std::cout << std::endl;
  }

  for( std::vector< LPDIRECTINPUTDEVICE8 >::iterator i = joysticks.begin(); i != joysticks.end(); ++i )
    if( *i )
      (*i)->Unacquire();

	return 0;
}

