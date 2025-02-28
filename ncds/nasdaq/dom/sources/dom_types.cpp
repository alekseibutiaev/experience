#include <limits>
#include <memory>
#include <iterator>
#include <algorithm>

#include "../dom_types.h"
#include "../../message.h"
#include "../message.h"

namespace nasdaq {

  namespace dom {

    const message_t::creators_t get_modile_info_t::m_creators = {
/* A */ [](const message_t& value){return std::make_unique<order_add_t>(value);},
/* B */ &message_t::empty,
/* C */ [](const message_t& value){return std::make_unique<order_executed_with_price_t>(value);},
/* D */ [](const message_t& value){return std::make_unique<order_delete_t>(value);},
/* E */ [](const message_t& value){return std::make_unique<order_executed_t>(value);},
/* F */ &message_t::empty,
/* G */ &message_t::empty,
/* H */ &message_t::empty,
/* I */ &message_t::empty,
/* J */ &message_t::empty,
/* K */ &message_t::empty,
/* L */ &message_t::empty,
/* M */ &message_t::empty,
/* N */ &message_t::empty,
/* O */ &message_t::empty,
/* P */ &message_t::empty,
/* Q */ &message_t::empty,
/* R */ &message_t::empty,
/* S */ [](const message_t& value){return std::make_unique<system_event_t>(value);},
/* T */ &message_t::empty,
/* U */ &message_t::empty,
/* V */ &message_t::empty,
/* W */ &message_t::empty,
/* X */ [](const message_t& value){return std::make_unique<order_cancel_t>(value);},
/* Y */ &message_t::empty,
/* Z */ &message_t::empty
    };

    const message_t::module_info_t get_modile_info_t::operator()() const {
      return message_t::module_info_t(m_creators, "dom", "msgType");
    }

  } /* namespace dom */

} /* namespace nasdaq */
