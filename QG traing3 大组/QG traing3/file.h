#pragma once
#include <stdio.h>
#include <stdlib.h>
//生成测试数据并保存到文件中
void generate_test_data(const char* filename, int n) {
    FILE* file = fopen(filename, "w");
    for (int i = 0;i < n;i++) {
        int value = rand() % (n * 10); //这里随便改，数据范围可以自行调整
        fprintf(file, "%d\n", value);
    }
    fclose(file);
}
//从文件中读取测试数据
int* read_test_data(const char* filename, int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    FILE* file = fopen(filename, "r");
    for (int i = 0;i < n;i++) {
        fscanf(file, "%d\n", &arr[i]);
    }
    fclose(file);
    return arr;
}