#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>

#include "sort.h"
#include "search.h"

#include "hello.h"

namespace py = pybind11;
using namespace lcc;

PYBIND11_MODULE(_lcclib, m) {
    m.doc() = R"pbdoc(
        Python module wrapper for LCC C++ library.
    )pbdoc";

    m.def("test", &lcc::hello);

    m.def("binarySearch", &lcc::binarySearch<long>);
    m.def("binarySearch", &lcc::binarySearch<int>);
    m.def("binarySearch", &lcc::binarySearch<char>);
    m.def("binarySearch", &lcc::binarySearch<double>);
    m.def("binarySearch", &lcc::binarySearch<float>);

    m.def("selectionSort", &lcc::selectionSort<long>);
    m.def("selectionSort", &lcc::selectionSort<int>);
    m.def("selectionSort", &lcc::selectionSort<char>);
    m.def("selectionSort", &lcc::selectionSort<double>);
    m.def("selectionSort", &lcc::selectionSort<float>);
    m.def("insertionSort", &lcc::insertionSort<long>);
    m.def("insertionSort", &lcc::insertionSort<int>);
    m.def("insertionSort", &lcc::insertionSort<char>);
    m.def("insertionSort", &lcc::insertionSort<double>);
    m.def("insertionSort", &lcc::insertionSort<float>);
    m.def("mergeSort", &lcc::mergeSort<long>);
    m.def("mergeSort", &lcc::mergeSort<int>);
    m.def("mergeSort", &lcc::mergeSort<char>);
    m.def("mergeSort", &lcc::mergeSort<double>);
    m.def("mergeSort", &lcc::mergeSort<float>);
    
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

}
