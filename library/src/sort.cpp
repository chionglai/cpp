

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

template <typename T>
void merge(std::vector<T>& list, int lo, int mid, int hi, std::vector<T>& aux) {
    int i = lo, j = mid + 1;
    int k;

    for (k = lo; k <= hi; k++)
        aux[k] = list[k];

    for (k = lo; k <= hi; k++) {
        if      (i > mid)         list[k] = aux[j++];
        else if (j > hi)          list[k] = aux[i++];
        else if (aux[j] < aux[i]) list[k] = aux[j++];
        else                      list[k] = aux[i++];
    }
}

template <typename T>
void sort(std::vector<T>& list, int lo, int hi, std::vector<T>& aux) {
    int mid;
    if (hi >= lo) return;
    mid = lo + (hi - lo) / 2;
    sort(list, lo, mid, aux);
    sort(list, mid + 1, hi, aux);
    merge(list, lo, mid, hi, aux);
}

template <typename T>
std::vector<T> lcc::mergeSort(std::vector<T>& unsorted) {
    std::vector<T> aux(unsorted.size());
    sort(unsorted, 0, unsorted.size(), aux);
    return unsorted;
}

template <typename T>
std::vector<T> lcc::quickSort(std::vector<T>& unsorted) {
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

template std::vector<long> lcc::mergeSort(std::vector<long>&);
template std::vector<int> lcc::mergeSort(std::vector<int>&);
template std::vector<char> lcc::mergeSort(std::vector<char>&);
template std::vector<double> lcc::mergeSort(std::vector<double>&);
template std::vector<float> lcc::mergeSort(std::vector<float>&);
