#pragma once

#include <map>
#include <shared_mutex>

#include "types.h"

namespace nasdaq {

  class decoder_t;

  class table_manager_t {
  public:
    virtual ~table_manager_t() = default;
    virtual void table(const std::string& stream, const std::string& msg, const fields_t& fields) = 0;
    virtual void record(const std::string& stream, const std::string& msg, const std::size_t& sn,
      const decoder_t& decoder, const record_ptr record, const time_point_t& tp) = 0;
    virtual bool save(const std::string& stream, const std::string& schema) = 0;
    virtual std::string load(const std::string& stream) = 0;
    const fields_t& get_fields(const std::string& stream, const std::string& msg) const;
  private:
    using msg_fields_t = std::map<std::string, fields_t>;
    using stream_msg_t = std::map<std::string, msg_fields_t>;
  private:
    mutable std::shared_mutex m_lock_stream_msg;
    stream_msg_t m_stream_msg;
  };

} /* namespace nasdaq */
