// use_com.cpp : Defines the entry point for the console application.
//
// http://www.planar.chel.ru/Products/Measurement%20instrument/OBZOR
//
#include "stdafx.h"
#include <iostream>

#import "Obzor103.exe" named_guids

int _tmain( int ac, _TCHAR* av[] ) {
  Obzor102::IAutomationPtr am = 0;
  if( S_OK != CoInitialize(NULL) ) {
    std::cerr << "can`t initialize COM subsystem." << std::endl;
    return !S_OK;
  }
  if( S_OK != am.CreateInstance( __uuidof( Obzor102::Automation ) ) ) {
    std::cerr << "Failed 0x" << std::endl;
    return !S_OK;
  }
  am->Minimize();
  ::Sleep( 8000 );
  am->ResetState();
  am->gStart = 1.5; // 1.5 MHz
  am->gStop = 30.0; // 30 MHz
  const double start = am->gStart;
  const double stop = am->gStop;

  const long points = static_cast< long >( ( stop - start ) / 0.1 ) + 1;
  am->gPoints = points;
  am->ReceiverConfig = Obzor102::rcAinBrl;
  am->chTraceFormat[ 0 ] = Obzor102::tfLinMag;
  am->chPort[ 0 ] = 1;
  am->chTraceFormat[ 1 ] = Obzor102::tfLinMag;
  am->chPort[ 1 ] = 1;
  am->TakeCompleteSweep();
  const VARIANT freq_v = am->gFrequencies;
  const VARIANT values0_v = am->chValues[ 0 ];
  const VARIANT values1_v = am->chValues[ 1 ];
  std::cout << "0x" << std::hex << freq_v.vt << std::dec << std::endl;
  std::cout << "0x" << std::hex << values0_v.vt << std::dec << std::endl;
  std::cout << "0x" << std::hex << values1_v.vt << std::dec << std::endl;
  const double* freq = reinterpret_cast< const double* >( freq_v.lVal );
  const double* values0 = reinterpret_cast< const double* >( values0_v.lVal );
  const double* values1 = reinterpret_cast< const double* >( values1_v.lVal );
  for( long i = 0; i < points; ++i )
    std::cout << "Freq: " << freq[ i ] << " value0: " << values0[ i ] <<
     " value1: " << values1[ i ] << std::endl;
#if 0
  std::cout << "Press ENTER to exit." << std::endl;
  getc( stdin );
#endif
  // Release COM object
  am.Release();
  CoUninitialize();
  std::cout << points << std::endl;
  return 0;
}
