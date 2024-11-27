#pragma once

#include "types.h"

namespace nasdaq {

  class error_t;

  class record_t {
  public:
    record_t(const get_property_t& get_property, const error_t& err);
    virtual ~record_t() = default;
  protected:
    const error_t& m_error;
    const get_property_t m_get_property;
  protected:
    static std::size_t m_idx_type;
  };

} /* namespace nasdaq */
