#include <iostream>
#include <boost/python.hpp>

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_mymodule
    extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initmymodule
    extern "C" void INIT_MODULE();
#endif

int main(int ac, char* av[]) {
  try {
      // Initialize the Python interpreter.
    Py_Initialize();
    // Add the current directory to the path.
    boost::python::import("sys").attr("path").attr("append")(".");
    // Get the "hello_from_python" function from "hello.py".
    boost::python::object func = boost::python::import("pyprog").attr("get_message");
    boost::python::object func1 = boost::python::import("pyprog").attr("get_message_param");
    // Call the "hello_from_python" and extract the return value as a string.
    std::string return_value = boost::python::extract<std::string>(func());
    std::string param = boost::python::extract<std::string>(func1("parametr"));
    // Print out the return value.
    std::cout << "Return value: '" << return_value << "'" << std::endl;
    std::cout << "Return value: '" << param << "'" << std::endl;
  } catch (boost::python::error_already_set& e) {
    PyErr_PrintEx(0);
    return 1;
  }
  return 0;
}