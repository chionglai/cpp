//
// Created by chiong on 5/10/17.
//

#ifndef __NDARRAY_H
#define __NDARRAY_H

#include <initializer_list>
#include <vector>
#include <limits>
#include <cstddef>

namespace lcc {

/** 
 * @brief Implement a N-dimensional array as a flat array.
 * @details In default, the data is laid out as (in order) row -> column -> higher dimensions.
 *      It provides API to return iterators that allows for walking the
 *      dimensions in different order as well as getting a slice/page of data.
 */
template<typename T>
class NdArray {
  public:
    static size_t END_OF_ARRAY = std::numeric_limits<std::size_t>::max();

    // Constructor to create N-dimensional array filled with zeros.
    explicit NdArray(const std::initializer_list<size_t> &dims);
    // Constructor to create N-dimensional array filled with init_value.
    NdArray(const std::initializer_list<size_t> &dims, T init_value);

    /**
     * @brief Return the dimensions of the N-dimensional array.
     * @returns Vector where its size() represent number of dimensions and
     *      each of its entry represents the count/size for that dimension.
     */
    // 
    const std::vector<size_t> &dims() const { return dims_; }

    /**
     * @brief Return an iterator for a given slice/page.
     * @param[in] sub_dims
     * @param[in] slice_pos
     * @param[in] order
     */
    StrideIterator GetSlice(const std::initializer_list<size_t> &sub_dims,
        const std::initializer_list<size_t> &slice_pos,
        const std::initializer_list<size_t> &order = {}) const;
    
    /**
     * @brief Return an iterator beginning at the specified pos.
     * @param[in] pos
     * @param[in] order
     * @param[in] count
     */
    StrideIterator GetIterator(const std::initializer_list<size_t> &pos, const std::initializer_list<size_t> &order = {}, size_t count = END_OF_ARRAY) const;

  private:
    std::vector<size_t> dims_;
    std::vector<T> data_;
};

template<typename T>
class StrideIterator {
  public:

  private:
    T *data_ptr_;
    size_t flat_index_;
    std::vector<size_t> dims_;
    std::vector<size_t> current_index_;


};

class IteratorWrapper {
  public:
    IteratorWrapper() {}

  private:

};

}   // namespace lcc



#endif  // __NDARRAY_H
