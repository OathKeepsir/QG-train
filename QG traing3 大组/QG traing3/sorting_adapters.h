// sorting_adapters.h

#ifndef SORTING_ADAPTERS_H
#define SORTING_ADAPTERS_H

#include "sorting_algorithms.h" 

void adapter_radix_sort(int* arr, int n) {
	radix_sort(arr, n);
}

void adapter_count_sort(int* arr, int n) {
	int max_value = getmax(arr, n);
	count_sort(arr, n, max_value);
}

void adapter_quick_sort(int* arr, int n) {
	quick_sort(arr, 0, n - 1);
}

void adapter_merge_sort(int* arr, int n) {
	merge_sort(arr, 0, n - 1);
}

void adapter_insert_sort(int* arr, int n) {
	insert_sort(arr, n);
}

#endif // SORTING_ADAPTERS_H
