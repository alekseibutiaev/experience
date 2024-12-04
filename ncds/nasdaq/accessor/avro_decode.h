#pragma once

#include <memory>
#include <vector>
#include <string>

#include "error.h"

#include "acc_types.h"


namespace nasdaq {

  class data_delegate_t;

  namespace acc {

    class table_manager_t;

    namespace details {

      class avro_decode_t;

    } /* namespace details */


    class avro_decode_t {
    public:
      avro_decode_t(table_manager_t& table, const error_t& err, const std::string& ctrl_schema = std::string());
      void operator()(const time_point_t& tp, const std::string& stream, const void* buf, const std::size_t size) const;
      void get_field(const avro_record_t& record, const std::size_t& idx, data_delegate_t& data) const;
    public:
      const static std::string control;
    private:
      using avro_decode_ptr = std::shared_ptr<details::avro_decode_t>;
    private:
      const error_t& m_err;
      avro_decode_ptr m_impl;
    };

  } /* namespace acc */

} /* namespace nasdaq */
