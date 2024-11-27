#include <limits>
#include <string>
#include <stdexcept>

#include "error.h"
#include "record.h"
#include "location.h"

namespace {

  std::size_t get_idx_type(const nasdaq::get_property_t& get_property, const nasdaq::error_t& error) {
    static const std::string param_name = "record/idx_type";
    static const std::string default_idx = "2";
    for(std::string value = get_property(param_name).value_or(default_idx);;value = default_idx)
      try {
        return std::stoull(value);
      }
      catch(const std::exception& e) {
        error.warning("can`t get parameters: [" + param_name + "] is: [" + value +
          "]. use default value: " + default_idx + __FILE_STR__);
        value = default_idx;      
      }
  }

}; /* namespace */


namespace nasdaq {

  std::size_t record_t::m_idx_type = std::numeric_limits<std::size_t>::max();

  record_t::record_t(const get_property_t& get_property, const error_t& error)
      : m_error(error)
      , m_get_property(get_property) {
    if(std::numeric_limits<std::size_t>::max() == m_idx_type)
      m_idx_type = get_idx_type(m_get_property, m_error);

  }

} /* namespace nasdaq */
