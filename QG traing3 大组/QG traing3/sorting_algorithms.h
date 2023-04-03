#pragma once
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//插入排序
void insert_sort(int* arr, int n) {

    for (int i = 1;i < n;i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void merge(int* arr, int l, int mid, int r) {
    int n1 = mid - l + 1;
    int n2 = r - mid;
    //计算两个子数组的长度：
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    //创建两个新的子数组 L 和 R，并将原数组 arr 的元素复制到这两个子数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    //初始化三个指针 i、j 和 k，分别指向 L、R 和 arr 的第一个元素
    int i = 0, j = 0, k = l;
    //进行比较
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    //比较结束，进行收尾，把剩余元素放进去
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    //释放内存
    free(L);
    free(R);
}
void merge_sort(int* arr, int l, int r) {//先进行拆分，递归

    if (l < r) {
        int mid = l + (r - l) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }

}
void quick_sort(int* arr, int l, int r) {

    int i = l, j = r, flag = arr[(l + r) / 2], temp;
    do {
        while (arr[i] < flag) i++;
        while (arr[j] > flag) j++;
        if (i <= j) {
            temp = arr[i];arr[i] = arr[j];arr[j] = temp;
            i++;j--;
        }
    } while (i <= j);
    if (l < j)quick_sort(arr, l, j);
    if (i < r)quick_sort(arr, i, r);

}
void count_sort(int* arr, int n, int max_value) {

    int* count = (int*)calloc(max_value + 1, sizeof(int));//利用calloc，将数据都初始化为0
    int* output = (int*)malloc(n * sizeof(int));
    for (int i = 0;i < n;i++) {
        count[arr[i]]++;//先统计个数
    }
    for (int i = 1;i < max_value;i++) {
        count[i] += count[i - 1];
    }//之后再记录比当前数据小于或等于的数据个数
    for (int i = n - 1;i >= 0;i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;//逆序遍历数组，是为了保持排序的稳定性，具有相同值的元素，在排序后的相对顺序与原来的相对顺序相同。
    }
    for (int i = 0;i < n;i++) {
        arr[i] = output[i];
    }
    free(count);
    free(output);

}
int getmax(int* arr, int n) {
    int max = arr[0];
    for (int i = 1;i < n;i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
//基数排序
void radix_sort(int* arr, int n) {//从最低位到最高位
    int max_value = getmax(arr, n);
    for (int exp = 1;max_value / exp > 0;exp *= 10) {
        int* output = (int*)malloc(n * sizeof(int));
        int count[10] = { 0 };
        for (int i = 0;i < n;i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1;i < 10;i++) {
            count[i] += count[i - 1];//跟计数排序同样的操作
        }
        for (int i = n - 1;i >= 0;i--) {//逆序遍历,arr[i] / exp) % 10这个整体意思为，某一位上的数字。
            output[count[(arr[i] / exp) % 10] - 1] = arr[i]; //将该数放入对应的位置。
            count[(arr[i] / exp) % 10]--;//对应的个数减少一个
        }
        for (int i = 0;i < n;i++) {
            arr[i] = output[i];
        }
        free(output);
    }

}