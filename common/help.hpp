#include <map>
#include <type_traits>

#include "tools.hpp"

namespace tools {

  template <typename map_t, typename key_t>
  auto get_from_map(map_t& map, const key_t& key) -> std::optional<typename map_t::mapped_type> {
    using ret_t = decltype(get_from_map<map_t, key_t>(map,key));
    const auto it = map.find(key);
    return it != map.end() ? ret_t(it->second) : ret_t();
  }

} /* namespace tools */
