#include "stdafx.h"

#include <windll/windll_template.hpp>

namespace windll {

  std::vector< double >::iterator keepvector::begin() {
    return pv_array.begin();
  }

}; /* namespace windll */
