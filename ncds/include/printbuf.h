#include <memory>
#include <iosfwd>

using ostream_ptr = std::shared_ptr<std::ostream>;

void pbuffer(const void* buf, const std::size_t& size);

ostream_ptr get_stream();
