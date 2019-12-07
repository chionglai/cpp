

#ifndef __SORT_H
#define __SORT_H

#include <vector>

namespace lcc {

/**
 * @brief Collection of sorting functions.
 * @param[in] unsorted Vector containing unsorted elements
 * @return A copy of sorted vector.
 */
template <typename T>
std::vector<T> selectionSort(std::vector<T> &unsorted);

template <typename T>
std::vector<T> insertionSort(std::vector<T> &unsorted);

template <typename T>
std::vector<T> mergeSort(std::vector<T> &unsorted);

template <typename T>
std::vector<T> quickSort(std::vector<T> &unsorted);

}   // namespace lcc


#endif  // __SORT_H
