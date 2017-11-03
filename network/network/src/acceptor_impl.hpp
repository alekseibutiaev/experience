#pragma once

#ifndef __NETWORK_ACCEPTOR_IMPL_HPP__
#define __NETWORK_ACCEPTOR_IMPL_HPP__

#include <string>
#include <list>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

#include <network/handler.hpp>

#include "session_owner_fwd.hpp"

namespace network {

  class session_owner;
  class acceptor;

  class acceptor_impl {
  public:
    acceptor_impl( const unsigned short& f_port, creator_ptr& f_creator );
    acceptor_impl( const std::string& f_address, const unsigned short& f_port, creator_ptr& f_creator );
    ~acceptor_impl();
    void use_face( acceptor*  f_face );
  private:
    void pv_accept();
    void pv_acceptor_handler( session_owner_ptr f_awaiting, const boost::system::error_code& f_error );
    void pv_store_session( session_owner_ptr f_session_owner );
    void pv_thread_routine();
  private:
    acceptor* pv_face;
    const std::string pv_address;
    const unsigned short pv_port;
    creator_ptr pv_creator;
    std::list< session_owner_ref > pv_sessions;
    boost::asio::io_service pv_service;
    boost::asio::ip::tcp::acceptor pv_acceptor;
    boost::thread pv_thread;
  };

}; /* namespace network */

#endif /* __NETWORK_ACCEPTOR_IMPL_HPP__ */
