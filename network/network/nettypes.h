#pragma once

#include <memory>
#include <vector>
#include <functional>

#include <boost/system/error_code.hpp>

namespace net {

  using error_code_t = boost::system::error_code;

  using buffer_t = std::vector<unsigned char>;
  using buffer_ptr = std::shared_ptr<buffer_t>;

  class context_t;
  using context_ptr = std::unique_ptr<context_t>;

  class acceptor_t;
  using acceptor_ptr = std::unique_ptr<acceptor_t>;

  class session_t;
  using session_ptr = std::shared_ptr<session_t>;

  using receive_func_t = std::function<void(const buffer_ptr)>;
  using disconnect_func_t = std::function<void(session_ptr, const error_code_t&)>;
  using accepted_func_t = std::function<void(session_ptr)>;
  using buffer_allocator_t = std::function<buffer_ptr(const buffer_t::value_type*, std::size_t)>;

  namespace details {

    class socket_t;
    using socket_ptr = std::unique_ptr<socket_t>;

  } /* namespace details */

} /* namespace net */