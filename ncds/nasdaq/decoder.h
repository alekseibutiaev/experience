#pragma once

#include "types.h"
#include "data_delegate.h"


namespace nasdaq {

  class decoder_t {
  public:
    virtual ~decoder_t() = default;
    virtual void operator()(const std::string& stream, const void* buf, const std::size_t& size, const std::size_t& sn, const time_point_t& tp) const = 0;
    virtual void get_field(const record_ptr record, const std::size_t& idx, data_delegate_t& data) const = 0;
  };

} /*namespace nasdaq*/