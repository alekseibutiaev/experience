#pragma once

#ifndef __NETWORK_SESSION_OWNER_HPP__
#define __NETWORK_SESSION_OWNER_HPP__

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>

#include <network/handler.hpp>
#include <network/buffer.hpp>

#include "session_owner_fwd.hpp"

namespace network {

  class socket;
  typedef boost::shared_ptr< socket > socket_ptr; 

  class session_owner : public session_transmiter, public boost::enable_shared_from_this< session_owner >,
    session_owner_ptr, boost::noncopyable {
  public:
    session_owner( session_receiver_ptr f_receiver );
    boost::asio::ip::tcp::socket& get_socket();
    void connect();
    void connected();
    void receive( const buffer_ptr& f_data );
    void transmit( const buffer_ptr& f_data );
    void close();
  private:
    typedef boost::shared_ptr< boost::thread > thread_ptr;
    typedef void(session_owner::*connect_notice_t)();
  private:
    ~session_owner();
    void pv_connected();
    void pv_connected_empty();
    static void pv_socket_process( session_owner* f_self );
  private:
    session_receiver_ptr pv_receiver;
    connect_notice_t pv_notice;
    socket_ptr pv_socket;
    thread_ptr pv_thread;
  };

}; /* namespace network  */

#endif /* __NETWORK_SESSION_OWNER_HPP__ */
