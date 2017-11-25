

#include "sort.h"
#include <iostream>

template <typename T>
std::vector<T> lcc::selectionSort(std::vector<T> &unsorted) {
    int idx;
    T temp;
    auto vecSize = unsorted.size();

    for (int i = 0; i < vecSize; i++) {
        idx = i;
        for (int j = i + 1; j < vecSize; j++) {
           idx = (unsorted[idx] < unsorted[j])? idx : j;
        }
        
        if (idx != i) {
            // swap
            temp = unsorted[i];
            unsorted[i] = unsorted[idx];
            unsorted[idx] = temp;
        }
    }

    return unsorted;
}

template <typename T>
std::vector<T> lcc::insertionSort(std::vector<T> &unsorted) {
    T temp;
    auto vecSize = unsorted.size();

    for (int i = 1; i < vecSize; i++) {
        for (int j = i; j > 0 && unsorted[j] < unsorted[j-1]; j--) {
            // swap
            temp = unsorted[j-1];
            unsorted[j-1] = unsorted[j];
            unsorted[j] = temp;
        }
    }

    return unsorted;
}

template std::vector<long> lcc::selectionSort(std::vector<long>&);
template std::vector<int> lcc::selectionSort(std::vector<int>&);
template std::vector<char> lcc::selectionSort(std::vector<char>&);
template std::vector<double> lcc::selectionSort(std::vector<double>&);
template std::vector<float> lcc::selectionSort(std::vector<float>&);

template std::vector<long> lcc::insertionSort(std::vector<long>&);
template std::vector<int> lcc::insertionSort(std::vector<int>&);
template std::vector<char> lcc::insertionSort(std::vector<char>&);
template std::vector<double> lcc::insertionSort(std::vector<double>&);
template std::vector<float> lcc::insertionSort(std::vector<float>&);
