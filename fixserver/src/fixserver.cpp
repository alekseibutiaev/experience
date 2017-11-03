// BondsProServer.cpp : Defines the entry point for the console application.
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
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SessionSettings.h>
#include "Application.h"

void wait()
{
  std::cout << "Type Ctrl-C to quit" << std::endl;
  while(true)
  {
    FIX::process_sleep(1);
  }
}

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
    FIX::SocketAcceptor acceptor( application, storeFactory, settings, logFactory );

    acceptor.start();
	//wait();
	while(true){
		FIX::process_sleep(5);
		application.sendXMessages();
	}
    acceptor.stop();
    return 0;
  }
  catch ( std::exception & e )
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
