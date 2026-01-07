#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../error.h"
#include "../decoder.h"

#include "acc_types.h"


namespace nasdaq {

  class data_delegate_t;
  class table_manager_t;

  namespace acc {

    namespace details {

      class avro_decoder_t;

    } /* namespace details */


    class avro_decoder_t : public decoder_t {
    public:
      avro_decoder_t(table_manager_t& table, const error_t& error, const std::string& ctrl_schema = std::string());
      void operator()(const std::string& stream, const void* buf, const std::size_t& size, const std::size_t& sn, const time_point_t& tp) const override;
      void get_field(const record_ptr record, const std::size_t& idx, data_delegate_t& data) const override;
    public:
      const static std::string control;
    private:
      using avro_decoder_ptr = std::shared_ptr<details::avro_decoder_t>;
    private:
      avro_decoder_ptr m_impl;
    };

  } /* namespace acc */

} /* namespace nasdaq */
