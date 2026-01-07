#include <boost/python.hpp>
#include <iostream>
#include <frameobject.h>
#include "mymodule.hpp"

//using namespace boost::python;

#if PY_MAJOR_VERSION >= 3
#   define INIT_MODULE PyInit_mymodule
    extern "C" PyObject* INIT_MODULE();
#else
#   define INIT_MODULE initmymodule
    extern "C" void INIT_MODULE();
#endif


int main(int argc, char** argv) {
  try {
    PyImport_AppendInittab((char*)"_mymodule", INIT_MODULE);
    Py_Initialize();
    boost::python::object main_module = boost::python::import("__main__");
    boost::python::dict main_namespace = boost::python::extract<boost::python::dict>(main_module.attr("__dict__"));
    boost::python::object mymodule = boost::python::import("_mymodule");
    main_namespace["testobj"] = Base("created on C++ side");
    main_namespace["testobj1"] = Base("test");
    exec_file("embedding.py", main_namespace, main_namespace);
    const Base& t = boost::python::extract<const Base&>(main_namespace["testobj1"]);
    std::cout << "C++ " << t.name() << std::endl;
  } catch (boost::python::error_already_set& e) {
    PyErr_PrintEx(0);
    return 1;
  }
  return 0;
}
