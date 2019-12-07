//
// Created by chiong on 5/10/17.
//

#ifndef __SEARCH_H
#define __SEARCH_H

//template <typename DataType>
//unsigned int searchSub(unique_ptr<DataType> *)

#include <string>
#include <vector>

namespace lcc {

/**
 * @brief Perform binary search.
 * @details If sorted contains repeated keys, the index for one
 *      of the keys will be returned. Which one exactly is undefined.
 * @param[in] sorted Vector of sorted elemets.
 * @param[in] key Key to search for.
 * @returns The index of vector, whose key is found in vector. -1 if
 *      key is not found.
 */
template <typename T>
int binarySearch(const std::vector<T> &sorted, const T key);

}   // namespace lcc

#endif // __SEARCH_H
