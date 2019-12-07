//
// Created by chiong on 5/10/17.
//

#include "../inc/search.h"

template <typename T>
int lcc::binarySearch(const std::vector<T> &sorted, const T key) {
    int left, right, mid;

    // Test for extreme cases
    if (sorted[0] == key) {
        return 0;
    } else if (sorted[sorted.size()-1] == key) {
        return sorted.size() - 1;
    } else {
        // perform binary search
        left = 0; right = sorted.size();
        while (left <= right) {
            mid = (left + right) / 2;
            if (sorted[mid] == key) {
                return mid;
            } else if (sorted[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;  // not found
    }
}


template int lcc::binarySearch(const std::vector<long>&, const long key);
template int lcc::binarySearch(const std::vector<int>&, const int key);
template int lcc::binarySearch(const std::vector<char>&, const char key);
template int lcc::binarySearch(const std::vector<double>&, const double key);
template int lcc::binarySearch(const std::vector<float>&, const float key);

