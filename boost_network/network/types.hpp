#pragma once

#include <vector>
#include <memory>
#include <functional>

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

namespace net {

  using buffrt_t = std::vector<unsigned char>;
  using buffer_ptr_t = std::shared_ptr<buffrt_t>;


  using error_code_t = boost::system::error_code;
  using service = boost::asio::io_service;

  using receive_callback_t = std::function<void(error_code_t, buffer_ptr_t)>;

} /* namespace net */
