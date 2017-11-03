#pragma once

#ifndef __NETWORK_SOCKET_HPP__
#define __NETWORK_SESSION_HPP__

#include <boost/asio.hpp>
#include <boost/utility.hpp>
#include <boost/smart_ptr.hpp>

#include <network/buffer.hpp>

namespace network {
  
  class session_owner;

  class socket : public boost::enable_shared_from_this< socket >, boost::noncopyable {
  public:
    socket( session_owner* f_owner );
    ~socket();
    boost::asio::ip::tcp::socket& get_socket();
    void run();
    void connected();
    void write( const buffer_ptr& f_data );
    void close();
    bool is_closed() const;
  private:
    typedef boost::shared_ptr< socket > socket_ptr;
  private:
    void pv_write_handler( socket_ptr f_socket, const buffer_ptr f_data,
      const boost::system::error_code& f_error, std::size_t f_bytes_transferred );
    void pv_read_handler( socket_ptr f_socket, buffer_ptr f_data,
      const boost::system::error_code& f_error, std::size_t f_bytes_transferred );
  private:
    session_owner* pv_owner;
    bool pv_closed;
    boost::asio::io_service pv_service;
    boost::asio::ip::tcp::socket pv_socket;
  private:
    static const unsigned long pv_buffer_size = 1024;
  };

}; /* namespace network */ 

#endif /*__NETWORK_SOCKET_HPP__*/