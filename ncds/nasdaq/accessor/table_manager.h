#pragma once

#include <map>
#include <shared_mutex>

#include "acc_types.h"

namespace nasdaq {

  namespace acc {

    class avro_decode_t;

    class table_manager_t {
    public:
      virtual ~table_manager_t() = default;
      virtual void table(const std::string& stream, const std::string& msg, const fields_t& fields) = 0;
      virtual void record(const avro_decode_t& decoder, const time_point_t& tp, const std::string& stream,
          const std::string& msg, const avro_record_t record) = 0;
      virtual bool save(const std::string& stream, const std::string& schema) = 0;
      virtual std::string load(const std::string& stream) = 0;
    protected:
      const fields_t& get_fields(const std::string& stream, const std::string& msg) const;
    private:
      using msg_fields_t = std::map<std::string, fields_t>;
      using stream_msg_t = std::map<std::string, msg_fields_t>;
    private:
      mutable std::shared_mutex m_lock_stream_msg;
      stream_msg_t m_stream_msg;
    };

  } /* namespace acc */

} /* namespace nasdaq */
