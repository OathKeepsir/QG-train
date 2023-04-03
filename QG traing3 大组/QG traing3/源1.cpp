#include <stdio.h>
#include <stdlib.h>
#include <time.h>
include"file.h"
include"sorting_algorithms.h"
//--------------------------------------------------
test_sort_time(void(*sort)(int*,int),int* data_test_size,const char *algorithm_name) {
    printf("\nĿǰ�� %s ��������\n", algorithm_name);
        for (int i = 0;i < 2;i++) {
            int n = data_test_size[i];
            const char* filename = "test_data.txt";
            generate_test_data(filename, n);
            clock_t start = clock();
            sort(arr, n);
            clock_t end = clock();
            double use_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\n���ݼ��Ĵ�СΪ:%d,��ʱ��%.4f seconds\n", n, use_time);
                free(arr);
        }
}
void test_small_data_time(void(*sort)(int*, int),int test_num, int n, const char* algorithm_name) {
    printf("\nĿǰ�� %s ��������\n", algorithm_name);
    const char* filename = "test_data.txt";
    generate_test_data(filename, n);
    int* arr = read_test_data(filename, n); //���ɺö�Ӧ��������
    clock_t start = clock();
    for (int i = 0;i < test_num;i++) {
        int* arr_copy = (int*)malloc(n * sizeof(int));//ϣ����ÿ���ظ����������㷨ʱ����������ͬ��δ�������������С��������ֱ�Ӷ�ԭʼ����arr���в�������ô�ڵ�һ�����������㷨֮��arr���Ѿ��������ˡ�
        memcpy(arr_copy, arr, n * sizeof(int));
        sort(arr_copy, n);
        free(arr_copy);
    }
    clock_t end = clock();
    double use_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n���ݼ��Ĵ�СΪ:%d,��ʱ��%.4f seconds\n", n, use_time);
    free(arr);
}
void run_sorting_algorithm(int algorithm_choice, int test_choice, int n) {
    void (*sorting_algorithm)(int*, int) = NULL;
    char* algorithm_name = NULL;

    switch (algorithm_choice) {
    case 1:
        sorting_algorithm = adapter_insert_sort;
        algorithm_name = "InsertSort";//��������
        break;
    case 2:
        sorting_algorithm = adapter_merge_sort;
        algorithm_name = "MergeSort";//�鲢����
        break;
    case 3:
        sorting_algorithm = adapter_quick_sort;//��������
        algorithm_name = "QuickSort (Recursive)";
        break;
    case 4:
        sorting_algorithm = adapter_count_sort;//��������
        algorithm_name = "CountSort";
        break;
    case 5:
        sorting_algorithm = adapter_radix_sort;//��������
        algorithm_name = "RadixCountSort";
        break;
    default:
        printf("��Ч�������㷨ѡ������������\n");
        return;
    }
    //��һ�ֲ��Է�ʽ
    if (test_choice == 1) {
        int data_test_size[] = { 10000,50000,200000 };
        test_sort_time(sorting_algorithm, data_test_size, algorithm_name);
    }//�ڶ��ֲ��Է�ʽ
    else if (test_choice == 2) {
        int test_num;
        printf("����������Ҫ��С���������ԵĴ���:\n");
        scanf("%d", &test_num);

        test_small_data_time(sorting_algorithm, test_num, n, algorithm_name);
    }//�����ֲ��Է�ʽ
    else {
        int* arr = (int*)malloc(n * sizeof(int));
        printf("�������� ", n);
        for (int i = 0; i < n; i++) {
            printf("����������������ǵ�%d������(��0��ʼ������", i);
            scanf("%d", &arr[i]);
        }
        printf("����ǰ: ");
        print_arr(arr, n);
        sorting_algorithm(arr, n);
        printf("����� : ");
        print_arr(arr, n);
        free(arr);
    }
}

int main() {
    while (1) {
        printf("\nѡ�������㷨:\n");
        printf("1. ��������\n");
        printf("2. �鲢����\n");
        printf("3. ��������\n");
        printf("4. ��������\n");
        printf("5. ��������\n");
        printf("6. �˳�\n");

        int algorithm_choice;
        printf("������: ");
        scanf("%d", &algorithm_choice);

        if (algorithm_choice == 6) {
            printf("���˳�\n");
            break;
        }

        printf("\nѡ���������:\n");
        printf("1. �ڲ�ͬ�Ĵ������������������ʱ\n");
        printf("2. �ڴ���С�����������������ʱ\n");
        printf("3. �����������ݣ����������ǰ�������Ľ��\n");

        int test_choice;
        printf("������: ");
        scanf("%d", &test_choice);

        int n;
        printf("\n���������ݼ��Ĵ�С����300������������300: ");
        scanf("%d", &n);

        run_sorting_algorithm(algorithm_choice, test_choice, n);
    }

    return 0;
}
