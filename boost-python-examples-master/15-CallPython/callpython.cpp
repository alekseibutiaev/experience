#include <iostream>
#include <boost/python.hpp>

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_mymodule
    extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initmymodule
    extern "C" void INIT_MODULE();
#endif
class py_initialize_t {
public:
  py_initialize_t() {
    Py_Initialize();
  }
  ~py_initialize_t() {
     Py_Finalize();
  }
};

int main(int ac, char* av[]) {
  try {
      // Initialize the Python interpreter.
    py_initialize_t ini;
    // Add the current directory to the path.
    boost::python::import("sys").attr("path").attr("append")(".");
    // Get the "get_message" and "get_message_param" function from "hello.py".
    boost::python::object func0 = boost::python::import("pyprog").attr("get_message");
    boost::python::object func1 = boost::python::import("pyprog").attr("get_message_param");
    // Call the "get_message" and extract the return value as a string.
    std::string res0 = boost::python::extract<std::string>(func0());
    // Call the "get_message_param" and extract the return value as a string.
    std::string res1 = boost::python::extract<std::string>(func1("parametr"));
    // Print out the return value.
    std::cout << "Return value: '" << res0 << "'" << std::endl;
    std::cout << "Return value: '" << res1 << "'" << std::endl;
  }
  catch (boost::python::error_already_set& e) {
    PyErr_PrintEx(0);
    return 1;
  }
  return 0;
}