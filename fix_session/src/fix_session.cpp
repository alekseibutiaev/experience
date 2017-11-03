//============================================================================
// Name        : fix_session.cpp
// Author      : Butyaev A
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>


#include <quickfix/Values.h>
#include <quickfix/Application.h>
#include <quickfix/Session.h>
#include <quickfix/TimeRange.h>
#include <quickfix/SessionID.h>
#include <quickfix/DataDictionaryProvider.h>
#include <quickfix/FieldTypes.h>
#include <quickfix/MessageStore.h>
#include <quickfix/Log.h>
#include <quickfix/Parser.h>
#include <quickfix/Responder.h>
#include <quickfix/MessageCracker.h>

class application_client : public FIX::Application, public FIX::MessageCracker {
public:
  /// Notification of a session begin created
  void onCreate( const FIX::SessionID& f_sid ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of a session successfully logging on
  void onLogon( const FIX::SessionID& f_sid ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of a session logging off or disconnecting
  void onLogout( const FIX::SessionID& f_sid ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of admin message being sent to target
  void toAdmin( FIX::Message& f_msg,  const FIX::SessionID& f_sid ) {
//  	f_msg.setField( FIX::Username( "jfdgjkdfgj" ) );
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of app message being sent to target
  void toApp( FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::DoNotSend ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of admin message being received from target
  void fromAdmin( const FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  /// Notification of app message being received from target
  void fromApp( const FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
  void onMessage( const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID& ) {
  	std::cout << "application_client " << __FUNCTION__ << std::endl;
  }
};

class application_server : public FIX::Application, public FIX::MessageCracker {
public:
  /// Notification of a session begin created
  void onCreate( const FIX::SessionID& f_sid ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of a session successfully logging on
  void onLogon( const FIX::SessionID& f_sid ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of a session logging off or disconnecting
  void onLogout( const FIX::SessionID& f_sid ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of admin message being sent to target
  void toAdmin( FIX::Message& f_msg,  const FIX::SessionID& f_sid ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of app message being sent to target
  void toApp( FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::DoNotSend ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of admin message being received from target
  void fromAdmin( const FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  /// Notification of app message being received from target
  void fromApp( const FIX::Message& f_msg,  const FIX::SessionID& f_sid ) throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
  void onMessage( const FIX44::MarketDataIncrementalRefresh& message, const FIX::SessionID& ) {
  	std::cout << "application_server " << __FUNCTION__ << std::endl;
  }
};

class responder : public FIX::Responder {
public:
	responder( FIX::Session& f_session ) : pv_session( f_session ) {
	}
  bool send( const std::string& f_msg ) {
  	std::cout << "responder " << __FUNCTION__<< " " << pv_session.getSessionID() << std::endl;
  	pv_parser.addToStream( &f_msg[ 0 ], f_msg.size() );
  	std::string msg;
		while( pv_parser.readFixMessage( msg ) ) {
			FIX::UtcTimeStamp time;
			pv_session.next( msg, time );
		}
		return true;
  }
  void disconnect() {
  	std::cout << "responder " << __FUNCTION__ << std::endl;
  }
private:
  FIX::Session& pv_session;
  FIX::Parser pv_parser;
};

int main() {
	try {
		FIX::Parser parser;		srand( time( 0 ) );

		application_client appc;
		application_server apps;
		FIX::MemoryStoreFactory msf;
		FIX::ScreenLogFactory slf( true, true, true );
		const FIX::SessionID sidab( FIX::BeginString_FIX43, "client", "server" );
		const FIX::SessionID sidba( FIX::BeginString_FIX43, "server", "client" );
		FIX::DataDictionaryProvider ddp;


		ddp.addTransportDataDictionary( FIX::BeginString( FIX::BeginString_FIX43 ), "spec/FIX43.xml" );
		const FIX::TimeRange tr( FIX::UtcTimeOnly( 0, 0, 0 ), FIX::UtcTimeOnly( 0, 0, 0 ) );

		FIX::Session client( appc, msf, sidab, ddp, tr, 60, &slf );
		FIX::Session server( apps, msf, sidba, ddp, tr, 60, &slf );
		responder resps( server );
		responder respc( client );
		client.setResponder( &resps );
		server.setResponder( &respc );
		for(;;)
			client.next();

#if 0
		sess.setResponder( &resp );
		char buf[ 2048 ];
		std::ifstream in( "Swiss.log", std::ios::binary );
		std::string msg;
		sess.next();
		while( in.good() ) {
			const int read = 1024 + rand() % 1024;
			in.read( buf, read );
			parser.addToStream( buf, read );

			while( parser.readFixMessage( msg ) ) {
				sess.next( msg, FIX::UtcTimeStamp() );
			}
		}
#endif
	}
	catch( const std::exception& e ) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
