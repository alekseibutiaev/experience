#include "stdafx.h"

#include <cassert>
#include <algorithm>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "acceptor_impl.hpp"

#include "socket.hpp"
#include "session_owner.hpp"
#if 0
void client_manager_impl::connect( const std::string& f_address, const unsigned short& f_port, owner_creator_f f_creator, void* f_user_data ) {
    bool create = false;
    session_owner* owner = f_creator( &create, f_user_data );
    boost::asio::ip::tcp::socket& socket = owner->session()->get_impl()->socket();
    try {
      boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( f_address ), f_port );
      socket.async_connect( endpoint, boost::bind( &client_manager_impl::pv_connect_handler, this, owner, create,
        f_address, f_port, f_creator, boost::asio::placeholders::error ) );
    }
    catch( const boost::system::system_error& e ) {
      network::network_logger_singleton::Instance()->out( network::network_logger::eWarning, "client_manager_impl::connect: "
        "address is wrong %s:%d. reason: \"%s\". To try use DNS.\n", f_address.c_str(), f_port, e.what() );
      try {
        boost::asio::ip::tcp::resolver resolver( socket.get_io_service() );
        boost::asio::ip::tcp::resolver::query query( f_address, boost::lexical_cast< std::string >( f_port ) );
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
        boost::asio::async_connect( socket, iterator, boost::bind( &client_manager_impl::pv_connect_handler,
          this, owner, create, f_address, f_port, f_creator, boost::asio::placeholders::error ) );
      }
      catch( const boost::system::system_error& e ) {
        network::network_logger_singleton::Instance()->out( network::network_logger::eError, "client_manager_impl::connect: "
          "can`t resolved address %s:%d reason: \"%s\".\n", f_address.c_str(), f_port, e.what() );
        if( create )
          delete owner;
      }
    }
  }

// acceptor

  inline boost::asio::ip::tcp::endpoint create_endpoint( const std::string& f_address, const unsigned short& f_port ) {
    try {
      return boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( f_address ), f_port );
    }
    catch( const boost::system::system_error& ) {
      static const char* localhost = "127.0.0.1";
      network::network_logger_singleton::Instance()->out( network::network_logger::eError,
        "create_endpoint: invalid address %s use localhost.\n", f_address.c_str() );
      return boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( localhost ), f_port );
    }
  }

#endif

namespace {

  inline boost::asio::ip::tcp::endpoint create_endpoint( const std::string& f_address, const unsigned short& f_port ) {
    try {
      return boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( f_address ), f_port );
    }
    catch( const boost::system::system_error& ) {
      static const char* localhost = "127.0.0.1";
      std::cerr << "create_endpoint: invalid address %s use localhost." << std::endl;
      return boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string( localhost ), f_port );
    }
  }

  class close_session {
  public:
    void operator()( network::session_owner_ref& f_value ) const {
      if( network::session_owner_ptr ses = f_value.lock() )
        ses->close();
    }
  };

  class invalid {
  public:
    bool operator()( network::session_owner_ref& f_value ) const {
      return !static_cast< bool >( f_value.lock() );
    }
  };

}; /* namespace */

namespace network {

  acceptor_impl::acceptor_impl( const unsigned short& f_port, creator_ptr& f_creator ) :
      pv_face( 0 ), pv_address(), pv_port( f_port ), pv_creator( f_creator ), pv_service(),
        pv_acceptor( pv_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), pv_port ) ) {
    std::cout << "acceptor_impl::acceptor_impl 0x" << this << std::endl;
    pv_accept();
  }

  acceptor_impl::acceptor_impl( const std::string& f_address, const unsigned short& f_port, creator_ptr& f_creator ) :
      pv_face( 0 ), pv_address( f_address ), pv_port( f_port ), pv_creator( f_creator ), pv_service(),
        pv_acceptor( pv_service, create_endpoint( pv_address, pv_port ) ) {
    std::cout << "acceptor_impl::acceptor_impl 0x" << this << std::endl;
    pv_accept();
  }

  acceptor_impl::~acceptor_impl() {
    std::cout << "acceptor_impl::~acceptor_impl 0x" << this << std::endl;
    pv_acceptor.close();
    pv_thread.join();
    std::for_each( pv_sessions.begin(), pv_sessions.end(), close_session() );
  }

  void acceptor_impl::use_face( acceptor*  f_face ) {
    pv_face = f_face;  
  }

  void acceptor_impl::pv_accept() {
    session_receiver_ptr receiver = pv_creator->create();
    session_owner_ptr awaiting( ( new session_owner( receiver ) )->shared_from_this() );
    pv_acceptor.async_accept( awaiting->get_socket(), boost::bind( &acceptor_impl::pv_acceptor_handler, this,
      awaiting, boost::asio::placeholders::error ) );
    if( !pv_thread.joinable() )
      pv_thread = boost::thread( boost::bind( &acceptor_impl::pv_thread_routine, this ) );
  }

  void acceptor_impl::pv_acceptor_handler( session_owner_ptr f_awaiting, const boost::system::error_code& f_error ) {
    std::cout << "acceptor_impl::pv_acceptor_handler id: " << boost::this_thread::get_id() << std::endl;
    if( !f_error ) {
      f_awaiting->connected();
      pv_store_session( f_awaiting );
    }
    else {
      std::cerr << "acceptor_impl::pv_acceptor_handler error: " << f_error.value() << std::endl;
      f_awaiting->close();
    }
    if( pv_acceptor.is_open() )
      pv_accept();
  }

  void acceptor_impl::pv_store_session( session_owner_ptr f_session_owner ) {
    pv_sessions.erase( std::remove_if( pv_sessions.begin(), pv_sessions.end(), invalid() ),
      pv_sessions.end() );
    pv_sessions.push_back( f_session_owner );
  }

  void acceptor_impl::pv_thread_routine() {
    try {
      pv_service.run();
    }
    catch( const std::exception& e ) {
      std::cerr << "acceptor_impl::pv_thread_routine: stoped: " << e.what() << std::endl;
    }
  }

}; /* namespace network */
