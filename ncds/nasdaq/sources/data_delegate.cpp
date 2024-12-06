#include "data_delegate.h"

namespace nasdaq {

  long_wrp_t::long_wrp_t(const long& value)
    : m_value(value){
  }
  long_wrp_t::operator long() const {
    return m_value;
  }


  void data_delegate_t::data(const std::size_t& idx, const std::string& field, const long& value) {
    if("uniqueTimestamp" == field || "trackingID" == field) {
      union { struct { long ts : 48; short ctr : 16; } data; long _long; } val;
      val._long = value;
      data(idx, field, nasdaq::clock_t::time_point(nasdaq::clock_t::duration(val.data.ts)));
    }
    else
      data(idx, field, long_wrp_t(value));
  }

} /* namespace nasdaq */