#include <string>

class Base {
public:
  Base();
  Base(const std::string& name);
  virtual ~Base();
  std::string name() const;
  std::string get_name() const;
  void set_name(const std::string& val);
private:
  std::string mName;
};
