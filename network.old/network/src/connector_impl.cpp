#include "stdafx.h"

#include <string>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <network/handler.hpp>

#include "session_owner.hpp"
#include "connector_impl.hpp"

#if 0
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
#endif

namespace network {

  connector_impl::connector_impl() : pv_face( 0 ) {
  }

  connector_impl::~connector_impl() {
  }

  void connector_impl::use_face( connector* f_face ) {
    pv_face = f_face;
  }

  void connector_impl::connect( const std::string& f_address, const unsigned short& f_port, creator* f_creator ) {
    session_receiver_ptr receiver = f_creator->create();
    session_owner_ptr awaiting( ( new session_owner( receiver ) )->shared_from_this() );
    boost::asio::ip::tcp::socket& socket = awaiting->get_socket();
    try {
      boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( f_address ), f_port );
      socket.async_connect( endpoint, boost::bind( &connector_impl::pv_connect_handler, this, awaiting,
        boost::asio::placeholders::error ) );
    }
    catch( const boost::system::system_error& e ) {
      std::cout << "connector_impl::connect: address is wrong " << f_address << " potr: " << f_port << " reason: "
        << e.code().value() << std::endl;
      try {
        boost::asio::ip::tcp::resolver resolver( socket.get_io_service() );
        boost::asio::ip::tcp::resolver::query query( f_address, boost::lexical_cast< std::string >( f_port ) );
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
        boost::asio::async_connect( socket, iterator, boost::bind( &connector_impl::pv_connect_handler, this,
          awaiting, boost::asio::placeholders::error ) );
      }
      catch( const boost::system::system_error& e ) {
        std::cout << "connector_impl::connect: can`t resolved address: " << f_address <<
          ":" << f_port << " reason: " <<  e.code().value() << std::endl;
        awaiting->close();
        return;
      }
      awaiting->connect();
    }
  }

  void connector_impl::pv_connect_handler( session_owner_ptr f_awaiting, const boost::system::error_code& f_error ) {
    if( f_error )
      f_awaiting->close();
    else
      f_awaiting->connected();
  }

}; /* namespace network */
