// BondsProClient.cpp : Defines the entry point for the console application.
//

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
//#include "config.h"
#endif

#include <string>
#include <iostream>
#include <fstream>

#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/SessionSettings.h>
#include "Application.h"


int main( int argc, char** argv )
{
  if ( argc != 2 )
  {
    std::cout << "usage: " << argv[ 0 ]
    << " FILE." << std::endl;
    return 0;
  }
  std::string file = argv[ 1 ];

  try
  {
    FIX::SessionSettings settings( file );

    Application application;
    FIX::FileStoreFactory storeFactory( settings );
    FIX::FileLogFactory logFactory( settings );
    FIX::SocketInitiator initiator( application, storeFactory, settings, logFactory);

    initiator.start();
    application.run();
    initiator.stop();

    return 0;
  }
  catch ( std::exception & e )
  {
    std::cout << e.what();
    return 1;
  }
}
