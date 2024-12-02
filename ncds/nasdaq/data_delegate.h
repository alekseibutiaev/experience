
#include "types.h"

namespace nasdaq {

  class data_delegate_t {
  public:
    using fields_t = std::vector<std::string>;
  public:
    virtual ~data_delegate_t() = default;
    virtual void data(const std::string& field, const std::string& value) = 0;
    virtual void data(const std::string& field, const unsigned char& value) = 0;
    virtual void data(const std::string& field, const int& value) = 0;
    virtual void data(const std::string& field, const long& value) = 0;
    virtual void data(const std::string& field, const float& value) = 0;
    virtual void data(const std::string& field, const double& value) = 0;
    virtual void data(const std::string& field, const bool& value) = 0;
  };

} /* namespace nasdaq */