#include "stdafx.h"

#include <cassert>
#include <iostream>

#include <network/handler.hpp>

#include "socket.hpp"
#include "session_owner.hpp"

namespace {

  void empty_deliter( void* f_ptr ) {
    std::cout << "empty_deliter: 0x" << f_ptr << std::endl;
  }

}; /* namespace */

namespace network {

  session_owner::session_owner( session_receiver_ptr f_receiver ) : pv_receiver( f_receiver ),
      pv_notice( &session_owner::pv_connected ) {
    std::cout << "session_owner::session_owner 0x" << this << std::endl;
    session_owner_ptr::reset( this, empty_deliter() );
  }

  session_owner::~session_owner() {
    std::cout << "session_owner::~session_owner 0x" << this << std::endl;
    pv_receiver->closed();
  }

  boost::asio::ip::tcp::socket& session_owner::get_socket() {
    if( !pv_socket )
      pv_socket.reset( new socket( this ) );  
    return pv_socket->get_socket();
  }

  void session_owner::connect() {
    assert( pv_socket );
    pv_notice = &session_owner::pv_connected_empty;
    pv_thread.reset( new boost::thread( boost::bind( &session_owner::pv_socket_process, this ) ) );
  }

  void session_owner::connected() {
    assert( pv_socket );
    if( pv_thread )
      pv_connected();
    else
      pv_thread.reset( new boost::thread( boost::bind( &session_owner::pv_socket_process, this ) ) );
  }

  void session_owner::receive( const buffer_ptr& f_data ) {
    pv_receiver->receive( f_data );
  }

  void session_owner::transmit( const buffer_ptr& f_data ) {
    if( pv_socket )
      pv_socket->write( f_data );
  }

  void session_owner::close() {
    if( pv_socket ) {
      if( thread_ptr tmp = pv_thread ) {
        pv_socket->close();
        if( tmp->joinable() && boost::this_thread::get_id() != tmp->get_id() )
          tmp->join();
      }
      else
        delete this;
    }
  }

  void session_owner::pv_socket_process( session_owner* f_self ) {
    std::cout << "session_owner::pv_socket_process id: " << boost::this_thread::get_id() << " started." << std::endl;
    thread_ptr tmp = f_self->pv_thread;
    (f_self->*f_self->pv_notice)();
    f_self->pv_socket->run();
    f_self->pv_receiver->disconnected();
    tmp->detach();
    delete f_self;
  }

  void session_owner::pv_connected() {
    pv_socket->connected();
    pv_receiver->connected( this );
  }

  void session_owner::pv_connected_empty() {
  }

}; /* namespace network  */
