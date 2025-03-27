#include <limits>
#include <memory>
#include <iterator>
#include <algorithm>

#include "../dom_types.h"
#include "../../message.h"
#include "../messages.h"

namespace nasdaq {

  namespace dom {

    const message_t::creators_t get_modile_info_t::m_creators = {
/* A */ [](const message_t& value){return std::make_unique<order_add_t>(value);},
/* B */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* C */ [](const message_t& value){return std::make_unique<order_executed_with_price_t>(value);},
/* D */ [](const message_t& value){return std::make_unique<order_delete_t>(value);},
/* E */ [](const message_t& value){return std::make_unique<order_executed_t>(value);},
/* F */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* G */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* H */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* I */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* J */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* K */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* L */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* M */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* N */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* O */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* P */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* Q */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* R */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* S */ [](const message_t& value){return std::make_unique<system_event_t>(value);},
/* T */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* U */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* V */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* W */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* X */ [](const message_t& value){return std::make_unique<order_cancel_t>(value);},
/* Y */ [](const message_t& value){return std::make_unique<base_t>(value);},
/* Z */ [](const message_t& value){return std::make_unique<base_t>(value);}
    };

    const message_t::module_info_t get_modile_info_t::operator()() const {
      return message_t::module_info_t(m_creators, "dom", "msgType");
    }

  } /* namespace dom */

} /* namespace nasdaq */
