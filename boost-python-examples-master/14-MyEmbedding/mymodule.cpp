#include <boost/python.hpp>

#include "mymodule.hpp"

using namespace boost::python;

Base::Base()
  : mName("Base") {
}

Base::Base(const std::string& name)
  : mName(name) {
}

Base::~Base() {
}

std::string Base::name() const {
  return mName;
}

std::string Base::get_name() const {
  return mName;
}

void Base::set_name(const std::string& val) {
  mName = val;
}


BOOST_PYTHON_MODULE(mymodule) {
  class_<Base>("Base")
    .def("__str__", &Base::name)
    .add_property("value", &Base::get_name, &Base::set_name)
  ;
}
