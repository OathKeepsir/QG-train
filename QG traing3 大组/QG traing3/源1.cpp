#include <stdio.h>
#include <stdlib.h>
#include <time.h>
include"file.h"
include"sorting_algorithms.h"
//--------------------------------------------------
test_sort_time(void(*sort)(int*,int),int* data_test_size,const char *algorithm_name) {
    printf("\n目前以 %s 方法测试\n", algorithm_name);
        for (int i = 0;i < 2;i++) {
            int n = data_test_size[i];
            const char* filename = "test_data.txt";
            generate_test_data(filename, n);
            clock_t start = clock();
            sort(arr, n);
            clock_t end = clock();
            double use_time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\n数据集的大小为:%d,用时：%.4f seconds\n", n, use_time);
                free(arr);
        }
}
void test_small_data_time(void(*sort)(int*, int),int test_num, int n, const char* algorithm_name) {
    printf("\n目前以 %s 方法测试\n", algorithm_name);
    const char* filename = "test_data.txt";
    generate_test_data(filename, n);
    int* arr = read_test_data(filename, n); //生成好对应的数据量
    clock_t start = clock();
    for (int i = 0;i < test_num;i++) {
        int* arr_copy = (int*)malloc(n * sizeof(int));//希望在每次重复运行排序算法时，都能在相同的未排序数据上运行。如果我们直接对原始数组arr进行操作，那么在第一次运行排序算法之后，arr就已经被排序了。
        memcpy(arr_copy, arr, n * sizeof(int));
        sort(arr_copy, n);
        free(arr_copy);
    }
    clock_t end = clock();
    double use_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n数据集的大小为:%d,用时：%.4f seconds\n", n, use_time);
    free(arr);
}
void run_sorting_algorithm(int algorithm_choice, int test_choice, int n) {
    void (*sorting_algorithm)(int*, int) = NULL;
    char* algorithm_name = NULL;

    switch (algorithm_choice) {
    case 1:
        sorting_algorithm = adapter_insert_sort;
        algorithm_name = "InsertSort";//插入排序
        break;
    case 2:
        sorting_algorithm = adapter_merge_sort;
        algorithm_name = "MergeSort";//归并排序
        break;
    case 3:
        sorting_algorithm = adapter_quick_sort;//快速排序
        algorithm_name = "QuickSort (Recursive)";
        break;
    case 4:
        sorting_algorithm = adapter_count_sort;//计数排序
        algorithm_name = "CountSort";
        break;
    case 5:
        sorting_algorithm = adapter_radix_sort;//基数排序
        algorithm_name = "RadixCountSort";
        break;
    default:
        printf("无效的排序算法选择，请重新输入\n");
        return;
    }
    //第一种测试方式
    if (test_choice == 1) {
        int data_test_size[] = { 10000,50000,200000 };
        test_sort_time(sorting_algorithm, data_test_size, algorithm_name);
    }//第二种测试方式
    else if (test_choice == 2) {
        int test_num;
        printf("请输入你想要在小数据量测试的次数:\n");
        scanf("%d", &test_num);

        test_small_data_time(sorting_algorithm, test_num, n, algorithm_name);
    }//第三种测试方式
    else {
        int* arr = (int*)malloc(n * sizeof(int));
        printf("输入数据 ", n);
        for (int i = 0; i < n; i++) {
            printf("你现在输入的数据是第%d个数据(从0开始计数）", i);
            scanf("%d", &arr[i]);
        }
        printf("排序前: ");
        print_arr(arr, n);
        sorting_algorithm(arr, n);
        printf("排序后 : ");
        print_arr(arr, n);
        free(arr);
    }
}

int main() {
    while (1) {
        printf("\n选择排序算法:\n");
        printf("1. 插入排序\n");
        printf("2. 归并排序\n");
        printf("3. 快速排序\n");
        printf("4. 计数排序\n");
        printf("5. 基数排序\n");
        printf("6. 退出\n");

        int algorithm_choice;
        printf("请输入: ");
        scanf("%d", &algorithm_choice);

        if (algorithm_choice == 6) {
            printf("已退出\n");
            break;
        }

        printf("\n选择测试类型:\n");
        printf("1. 在不同的大数据量，输出排序用时\n");
        printf("2. 在大量小数据量，输出排序用时\n");
        printf("3. 自行输入数据，后输出排序前和排序后的结果\n");

        int test_choice;
        printf("请输入: ");
        scanf("%d", &test_choice);

        int n;
        printf("\n请输入数据集的大小，如300个数字则输入300: ");
        scanf("%d", &n);

        run_sorting_algorithm(algorithm_choice, test_choice, n);
    }

    return 0;
}
