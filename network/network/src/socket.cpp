#include "stdafx.h"

#include <cassert>
#include <exception>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/date_time.hpp>

#include "session_owner.hpp"

#include "socket.hpp"

namespace network {

  socket::socket( session_owner* f_owner ) : pv_owner( f_owner ), pv_closed( false ),
      pv_service(), pv_socket( pv_service ) {
    assert( pv_owner );
    std::cout << "socket::socket 0x" << this << std::endl;
  }

  socket::~socket() {
    std::cout << "socket::~socket 0x" << this << std::endl;
  }

  boost::asio::ip::tcp::socket& socket::get_socket() {
    return pv_socket;
  }

  void socket::run() {
    try {
      std::cout << "socket::run start thread id: " << boost::this_thread::get_id() << std::endl;
      pv_service.run();
    }
    catch( const std::exception& e ) {
      std::cerr << e.what() << std::endl;
    }
    std::cout << "socket::run stop thread id: " << boost::this_thread::get_id() << std::endl;
  }

  void socket::connected() {
    pv_read_handler( shared_from_this(), buffer_ptr( new buffer_ptr::element_type(
      socket::pv_buffer_size ) ), boost::system::error_code(), 0 ); 
  }

  void socket::write( const buffer_ptr& f_data ) {
//    std::cout << "socket::write 0x" << this << std::endl;
    if( !is_closed() )
      pv_socket.async_write_some( boost::asio::buffer( *f_data ), boost::bind( &socket::pv_write_handler,
        this, shared_from_this(), f_data,  boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred ) );
  }

  void socket::close() {
    if( !is_closed() ) {
      pv_closed = true;
      pv_socket.close();
    }
  }

  bool socket::is_closed() const {
    return pv_closed;
  }

  void socket::pv_write_handler( socket_ptr f_socket, const buffer_ptr f_data,
    const boost::system::error_code& f_error, std::size_t f_bytes_transferred ) {
//    std::cout << "socket::pv_write_handler id: " << boost::this_thread::get_id() << std::endl;
    if( f_error )
      close();
    if( is_closed() )
      return;
    if( const unsigned long size = f_data->size() - f_bytes_transferred ) {
      pv_socket.async_write_some( boost::asio::buffer( &f_data->front() + f_bytes_transferred, size ),
        boost::bind( &socket::pv_write_handler, this, shared_from_this(), f_data,
          boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred ) );
    }
  }

  void socket::pv_read_handler( socket_ptr f_socket, buffer_ptr f_data,
      const boost::system::error_code& f_error, std::size_t f_bytes_transferred ) {
//    std::cout << "socket::pv_read_handler thread id: " << boost::this_thread::get_id() << std::endl;
    if( f_error )
      close();
    if( is_closed() )
      return;
    if( 0 < f_bytes_transferred )
      pv_owner->receive( buffer_ptr( new buffer_ptr::element_type( &f_data->front(),
        &f_data->front() + f_bytes_transferred ) ) );
    pv_socket.async_read_some( boost::asio::buffer( *f_data ), boost::bind( &socket::pv_read_handler, this,
      shared_from_this(), f_data, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred ) );
  }

}; /* namespace network */