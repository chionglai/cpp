# LCC C++ library

# Overview
My C++ library that contains C++ functions I wrote. The library will be constantly updated. The library can be built into both static and shared library using cmake. The library also contains Python wrapper using [pybind11](https://github.com/pybind/pybind11). This allows the library functions to be called from Python.

# What's new
### Ver. 0.0.1
* Initial release

# Installation
### C++
To build and install the C++ library, use `cmake`, `make`, and `make install`:
```
cmake . -DCMAKE_INSTALL_PREFIX=<root path to installation directory>
make
make install
```

### Python
Before building the Python wrapper, the C++ library needs to be built. Then, the Python wrapper can be built and installed, i.e.
```
cmake .
make
pip install -e pybind11/
```
