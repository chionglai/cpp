

#ifndef __SORT_H
#define __SORT_H

#include <vector>

namespace lcc {
    template <typename T>
    std::vector<T> selectionSort(std::vector<T> &unsorted);

    template <typename T>
    std::vector<T> insertionSort(std::vector<T> &unsorted);
}


#endif  // __SORT_H
