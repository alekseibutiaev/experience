
#include "context_details.h"

#include "context.h"

namespace net {

  context_ptr context_t::create() {
    return context_ptr(new details::context_t());
  }

} /* namespace net */
