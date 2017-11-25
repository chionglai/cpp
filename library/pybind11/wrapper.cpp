#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>

#include "hello.h"

namespace py = pybind11;

PYBIND11_MODULE(_lcclib, m) {
    m.doc() = R"pbdoc(
        Python module wrapper for LCC C++ library.
    )pbdoc";

    m.def("test", &lcc::hello);
    
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}
