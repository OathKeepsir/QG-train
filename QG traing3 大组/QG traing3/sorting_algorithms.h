#pragma once
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
//��������
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
    //��������������ĳ��ȣ�
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    //���������µ������� L �� R������ԭ���� arr ��Ԫ�ظ��Ƶ�������������
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    //��ʼ������ָ�� i��j �� k���ֱ�ָ�� L��R �� arr �ĵ�һ��Ԫ��
    int i = 0, j = 0, k = l;
    //���бȽ�
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
    //�ȽϽ�����������β����ʣ��Ԫ�طŽ�ȥ
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
    //�ͷ��ڴ�
    free(L);
    free(R);
}
void merge_sort(int* arr, int l, int r) {//�Ƚ��в�֣��ݹ�

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

    int* count = (int*)calloc(max_value + 1, sizeof(int));//����calloc�������ݶ���ʼ��Ϊ0
    int* output = (int*)malloc(n * sizeof(int));
    for (int i = 0;i < n;i++) {
        count[arr[i]]++;//��ͳ�Ƹ���
    }
    for (int i = 1;i < max_value;i++) {
        count[i] += count[i - 1];
    }//֮���ټ�¼�ȵ�ǰ����С�ڻ���ڵ����ݸ���
    for (int i = n - 1;i >= 0;i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;//����������飬��Ϊ�˱���������ȶ��ԣ�������ֵͬ��Ԫ�أ������������˳����ԭ�������˳����ͬ��
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
//��������
void radix_sort(int* arr, int n) {//�����λ�����λ
    int max_value = getmax(arr, n);
    for (int exp = 1;max_value / exp > 0;exp *= 10) {
        int* output = (int*)malloc(n * sizeof(int));
        int count[10] = { 0 };
        for (int i = 0;i < n;i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1;i < 10;i++) {
            count[i] += count[i - 1];//����������ͬ���Ĳ���
        }
        for (int i = n - 1;i >= 0;i--) {//�������,arr[i] / exp) % 10���������˼Ϊ��ĳһλ�ϵ����֡�
            output[count[(arr[i] / exp) % 10] - 1] = arr[i]; //�����������Ӧ��λ�á�
            count[(arr[i] / exp) % 10]--;//��Ӧ�ĸ�������һ��
        }
        for (int i = 0;i < n;i++) {
            arr[i] = output[i];
        }
        free(output);
    }

}