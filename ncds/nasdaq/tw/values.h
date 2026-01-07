#pragma once

#include <vector>
#include <stdexcept>

#include "dom_types.h"

namespace nasdaq {

  namespace tw {

    template<std::size_t values_count>
    class values_t {
    public:
      using indexes_t = std::vector<std::size_t>;
    public:
      value_t& operator[](const std::size_t idx) {
        return m_values[idx % values_count];
      }
      const value_t& operator[](const std::size_t idx) const {
        return m_values[idx % values_count];
      }
    private:
      value_t m_values[values_count];

    };

  } /* namespace tw */

} /* namespace nasdaq */
