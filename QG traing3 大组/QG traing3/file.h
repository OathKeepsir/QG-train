#pragma once
#include <stdio.h>
#include <stdlib.h>
//���ɲ������ݲ����浽�ļ���
void generate_test_data(const char* filename, int n) {
    FILE* file = fopen(filename, "w");
    for (int i = 0;i < n;i++) {
        int value = rand() % (n * 10); //�������ģ����ݷ�Χ�������е���
        fprintf(file, "%d\n", value);
    }
    fclose(file);
}
//���ļ��ж�ȡ��������
int* read_test_data(const char* filename, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    FILE* file = fopen(filename, "r");
    for (int i = 0;i < n;i++) {
        fscanf(file, "%d\n", &arr[i]);
    }
    fclose(file);
    return arr;
}