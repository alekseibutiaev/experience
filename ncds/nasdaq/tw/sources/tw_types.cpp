#include <limits>
#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

#include "../tw_types.h"
#include "../../message.h"
#include "../messages.h"

namespace nasdaq {

  namespace tw {

    message_uptr default_creator(const message_t& value) {
#if 0
      auto res = std::make_unique<base_t>(value);
      auto s = res->type();
      std::cout << s << " " << res->sequence() << std::endl;
      std::cout << std::endl;
      return res;
#else
      return std::make_unique<base_t>(value);
#endif
    }

    const message_t::creators_t get_modile_info_t::m_creators = {
/* A */ [](const message_t& value){return std::make_unique<order_add_t>(value);},
/* B */ default_creator,
/* C */ [](const message_t& value){return std::make_unique<order_executed_with_price_t>(value);},
/* D */ [](const message_t& value){return std::make_unique<order_delete_t>(value);},
/* E */ [](const message_t& value){return std::make_unique<order_executed_t>(value);},
/* F */ default_creator,
/* G */ default_creator,
/* H */ default_creator,
/* I */ default_creator,
/* J */ default_creator,
/* K */ default_creator,
/* L */ default_creator,
/* M */ default_creator,
/* N */ default_creator,
/* O */ default_creator,
/* P */ default_creator,
/* Q */ default_creator,
/* R */ default_creator,
/* S */ [](const message_t& value){return std::make_unique<system_event_t>(value);},
/* T */ default_creator,
/* U */ default_creator,
/* V */ default_creator,
/* W */ default_creator,
/* X */ [](const message_t& value){return std::make_unique<order_cancel_t>(value);},
/* Y */ default_creator,
/* Z */ default_creator
    };

    const message_t::module_info_t get_modile_info_t::operator()() const {
      return message_t::module_info_t(m_creators, "dom", "msgType");
    }

  } /* namespace tw */

} /* namespace nasdaq */
