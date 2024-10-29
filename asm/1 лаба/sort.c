#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int comparison_count = 0; //счетчик сравнений
long long int swap_count = 0; //счетчик перемещений

double d_abs(double x)
{
    if (x < 0) return x * (-1.0);
    return x;
}

void pr_helper() //функция для комментариев
{
    printf("Данная программа предназначена для решения первого задания весеннего семестра на методы сортировки.\n");
    printf("Выполнена студентом 105ой группы Кирневым Юрием\n");
    printf("Вариант 3 4 1 4\n");
    printf("3. Вещественные числа двойной точности (double).\n");
    printf("4. Числа упорядочиваются по невозрастанию модулей, т.е. при сравнении элементов не учитывается знак.\n");
    printf("1 и 4 - методы сортировки пузырек(1) и быстрая сортировка с рекурсивной реализацией(4)\n \n");
    printf("Результаты приведены в таблице ниже:\n \n");
    printf("    n    init_type   buble_sort comparisons   buble_sort swaps   qsort comparisons   qsort swaps\n"); //названия столбцов таблицы результатов
}

void init_list(double *a, int n, int flag) {
    if(flag == 0) {//прямой порядок
        for (int i = 0; i < n; i++) {
            a[i] = i / 1.0;
        }
    } else if(flag == 1) { //обратный порядок
        for (int i = 0;  i <= n; i++) {
            a[n - 1 - i] = i / 1.0;
        }
    } 
    else {//случайный порядок
        for (int i = 0; i < n; i++) {
            double tmp;
            int x1 = rand();
            int x2 = rand();
            tmp = x1 / x2;
            a[i] = tmp;
        }
    }
}
void buble_sort(double* a, int n) //сортировка пузырьком
{
    double swap;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - 1; j++)
        {
            comparison_count++;
            if (d_abs(a[j]) < d_abs(a[j + 1]))
            {
                swap = a[j];
                a[j] = a[j + 1];
                a[j + 1] = swap;
                swap_count++;
            }
        }
    }
}

void quick_sort(double* a, int left, int right){ //Быстрая сортировка с рекурсивной реализацией

    int tmp_left = left, tmp_right = right;
    double swap;
    double pivot = a[(left + right) / 2];
    while (tmp_left <= tmp_right){
        while (d_abs(a[tmp_left]) > d_abs(pivot)){
            tmp_left++;
            comparison_count++;
        }
        comparison_count++;
        while (d_abs(a[tmp_right]) < d_abs(pivot)){
            tmp_right--;
            comparison_count++;
        }
        comparison_count++;
        if(tmp_left <= tmp_right) {
            if(d_abs(a[tmp_left]) < d_abs(a[tmp_right])) {
                swap = a[tmp_left];
                a[tmp_left] = a[tmp_right];
                a[tmp_right] = swap;
                swap_count++;
            }
        comparison_count++;
        tmp_left++;
        tmp_right--;
        }
    }
    if(left < tmp_right){
        quick_sort(a, left, tmp_right);
    }
    if(tmp_left < right){
        quick_sort(a, tmp_left, right);
    }
}
void f()
{
    int n[] = {10, 100, 1000, 10000}; //массив количеств элементов
    double* a, * b; //массив который будем сортировать (второй для второго вида сортировки)
    for(int i = 0 ; i < 4;i++){ //4 указано, так как 4 длина массива n = 4
        a = (double *) malloc(sizeof(double)* n[i]); //создаем массив нужной длины
        b = (double *) malloc(sizeof(double)* n[i]);//аналогично для копии
        for (int j = 0; j < 4; j++) //4 указано, так как у нас 4 варианта типов массива (прямой, обратный и два варианта случайного порядка)
        {
            init_list(a, n[i], j); //инициализация массива с параметрами длины и флага
            init_list(b, n[i], j); //тоже самое для копии
            printf("%5d", n[i]); //вывод в таблицу количества элементов
            if (j == 0) //вывод в таблицу типа инициализации
            {
                printf("     straight");
            }
            else if(j == 1)
            {
                printf("         back");
            }
            else
            {
                printf("       random");
            }
            comparison_count = 0;
            swap_count = 0;    
            buble_sort(a, n[i]);//сортировка пузырьком
            printf("%25lld %18lld", comparison_count, swap_count);
            comparison_count = 0;
            swap_count = 0;   
            quick_sort(b, 0, n[i] - 1); //Быстрая сортировка
            printf("%20lld %13lld\n", comparison_count, swap_count);
        }
    }
}
int main(void)
{
    srand(time(NULL));
    pr_helper(); //вывод комментариев к программе
    f(); //создание и вывод таблицы результатов
}