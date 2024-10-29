#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long int comparison_count = 0; //счетчик сравнений
long long int swap_count = 0; //счетчик перемещений

double d_abs(double x) //функция модуля для вещественных чисел
{
    if (x < 0) return x * (-1.0);
    return x;
}
void pr_list(double *a, int n){
    for(int i = 0; i < n; i++)
    {
        printf("%f ", a[i]);
    }
}
void pr_helper() //функция для комментариев
{
    printf("Результаты приведены в таблице ниже:\n \n");
    printf("    n    init_type   buble_sort comparisons   buble_sort swaps   qsort comparisons   qsort swaps\n"); //названия столбцов таблицы результатов
}

void init_list(double *a, int n, int flag) { //функция инициализации массива в зависимости
//от номера варианта (флага) и длины массива
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
            tmp = (x1 + 0.0) / (x2 + 0.0);
            a[i] = tmp;
        }
    }
}
void buble_sort(double* a, int n) //сортировка пузырьком
{
    double swap;//переменная для перестановки
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

    int tmp_left = left, tmp_right = right; //создаем копии краев для того чтобы потом 
                                           //вызвать изначальные значения в рекурсии
    double swap; //переменная для обмена переменной
    double pivot = a[(left + right) / 2]; //медианное значение с которым сравниваем числа
    while (tmp_left <= tmp_right){//идем слева направо увеличивая левую границу
        while (d_abs(a[tmp_left]) > d_abs(pivot)){ //сравниваем с медианой и пока больше идем в цикле
            tmp_left++;
            comparison_count++;
        }
        comparison_count++;
        while (d_abs(a[tmp_right]) < d_abs(pivot)){//также делаем с правой границей
            tmp_right--;
            comparison_count++;
        }
        comparison_count++;
        if(tmp_left <= tmp_right) { //если левая граница меньше правой то меняем местами элементы с этими номерами
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
        quick_sort(a, left, tmp_right); //делаем рекурсивный вызов для левой части 
    }
    if(tmp_left < right){
        quick_sort(a, tmp_left, right); // и рекурсия для правой
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
int main(int argc, char *argv[])
{
    srand(time(NULL)); //вызов для инициализации генератора случайных чисел 
    if (argc == 1 || !(strcmp(argv[1], "--help") && strcmp(argv[1], "--H")))
    {
        printf("Данная программа предназначена для решения первого задания весеннего семестра на методы сортировки.\n");
        printf("Выполнена студентом 105ой группы Кирневым Юрием\n");
        printf("Вариант 3 4 1 4\n");
        printf("3. Вещественные числа двойной точности (double).\n");
        printf("4. Числа упорядочиваются по невозрастанию модулей, т.е. при сравнении элементов не учитывается знак.\n");
        printf("1 и 4 - методы сортировки пузырек(1) и быстрая сортировка с рекурсивной реализацией(4)\n \n");
        printf("Для корректной работы программы введите в аргументах командной строки 3 числа\nПервое число - количество элементов массива\nВторое число - тип генерации массива (0 - прямой, 1 - обратный, 2 - случайный)\nТретье число указывает на тип сортировки 1 для сортировки методом пузырька, 2 для быстрой сортировки");
        return 0;   
    }
    if(argc != 4)
    {
        printf("Incorrect input\n");
        printf("Для справки введите в аргументах командной строки --help или --H");
        return 0;
    }
    int n = atoi(argv[1]); //длина массива
    int type = atoi(argv[2]);//тип генерации (0 - прямой, 1 - обратный, 2 - случайный, другие - недопустимый параметр)
    int sort_type = atoi(argv[3]); //тип сортировки 1 - пузырек, 2 - быстрая сортировка
    if (n == 0 && type == 0 && sort_type == 0){
        pr_helper();
        f();
        return 0;
    }
    if (type >= 3 || type < 0 || sort_type < 0 || sort_type > 2 || n < 0){
        printf("Incorrect input\n");
        printf("Для справки введите в аргументах командной строки --help или --H");
        return 0;
    }
    double* a;
    a = (double *) malloc(sizeof(double)* n); //создаем массив, с которым будем работать 
    init_list(a, n, type); //инициализируем его, согласно аргументам командной строки
    printf("Cозданный массив: ");
    pr_list(a, n); //функция печати массив (сортировки)
    printf("\n");
    comparison_count = 0;
    swap_count = 0;
    if (sort_type == 1) buble_sort(a, n); //сортировка
    else quick_sort(a, 0, n - 1);
    printf("Отсортированный массив: ");
    pr_list(a, n); 
    printf("\nКоличество сравнений %lld \nКоличество перемещений %lld", comparison_count, swap_count);
}