#include "../inc/ndarray.h"

namespace lcc {

template<typename T>
NdArray<T>::NdArray(const std::initializer_list<size_t> &dims, T init_value)
  : dims_(dims) {
    size_t total_size = 1;
    for (auto dim : dims) {
        total_size *= dim;
    }
    data_.resize(total_size, init_value);
}

template<typename T>
NdArray<T>::NdArray(const std::initializer_list<size_t> &dims) {
    NdArray<T>(dims, 0);
}


}   // namespace lcc
