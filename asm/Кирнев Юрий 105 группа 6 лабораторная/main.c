#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);
extern double f1pr (double x);
extern double f2pr (double x);
extern double f3pr (double x);

double root(double(*f)(double), double(*fpr)(double), double(*g)(double), double(*gpr)(double), double a, double b, double eps1)// функция вычисления корня 
{
    double prev; //значение на предыдущем шаге 
    double tmp = prev + 2 * eps1; //значение на текущем шаге
    while(1)
    {
        if (fabs(prev - tmp) <= eps1) // сравниваем последние 2 итерации и если модуль разницы между ними меньше eps, то решение найдено 
        {
            return tmp; //возвращаем найденное решение
        }
        prev = tmp; //переприсваиваем 
        tmp = tmp - (f(tmp) - g(tmp)) / (fpr(tmp) - gpr(tmp)); //пересчитываем значение итерационной последовательности по методу касательных
    } 
}

double integral(double(*f)(double), double a, double b, double eps2)//функция для вычисления интеграла
{
    //I = (0.5 * F0 + F1 + F2 + ... + Fn-1 + 0.5 * Fn) - метод трапеций
    double n = 2; // количество разбиений
    double xk; // точка разбиения
    double prev; //значение до текущего разбиения
    double tmp = prev + 20 * eps2; //значение после текущего разбиения
    if (a > b){
      prev = a;
      a = b;
      b = prev;
    }
    while(1)
    {
        if (fabs(tmp - prev) / 3.0 <= eps2) // сравниваем последние 2 итерации и если модуль разницы между ними меньше eps, то интеграл вычислен (c учетом правила Рунге)
        {
            return tmp; //возвращаем найденное значение
            break;
        }
        else
        {
            prev = tmp; //переприсваиваем к значению до разбиения, значение после него 
            tmp = f(a) + f(b); 
            tmp = tmp / 2.0; //по методу трапеций добавляем граничные деленные пополам
            for (double i = 1.0; i < n / 2; i += 1.0)
            {
                xk = a + (b - a) * 2 * i / n; //добавляем остальные значения разбиения
                tmp += f(xk);
            }
            tmp *= (b - a) / n;
            n = n * 2; //увеличиваем количество разбиений
        }
    }
}

int main(int argc, char *argv[])
{
    double eps1 = 0.0001; //точность вычисления корня уравнения
    double eps2 = 0.0001; //точность вычисления величины определенног интеграла
    double answerf1f2 = root(f1, f1pr, f2, f2pr, 1, 2, eps1); //значение корня для уравнения f1 = f2
    double answerf2f3 = root(f2, f2pr, f3, f3pr, -1, -0.1, eps1); //значение корня для уравнения f2 = f3
    double answerf1f3 = root(f1, f1pr, f3, f3pr, -3, -2, eps1); //значение корня для уравнения f1 = f3
    if (argc <= 1)
    {
        printf("\n");
        printf("Данная программа предназначена для решения шестого задания весеннего семестра: \n «Сборка многомодульных программ. Вычисление корней уравнений и определенных интегралов»\n");
        printf("Выполнена студентом 105ой группы Кирневым Юрием\n");
        printf("Вариант 8 3 2\n");
        printf("8. Функции f1 = e^x + 2, f2 = -2x + 8, f3 = -5/x\n");
        printf("3. Метод приближенного решения уравнений с помощью метода касательных (Ньютона)\n");
        printf("2. Квадратурная формула для вычисления интегралов - формула трапеций\n");
        printf ("Для справки введите в аргументах командной строки --help или -H\n");
    }
    else if (strcmp(argv[1], "-H") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("\n");
        printf("При запуске программы без аргументов будет выведена информация об условии лабораторной работы\n");
        printf("Для запуска программы используйте следующие ключи:\n");
        printf("--root или -R без аргументов выведет координаты всех трех точек пересечения\n");
        printf("--integral или -I выведет искомую площадь\n");
        printf("--root_test f g a b eps\n f и g - числа из диапазона {1, 2, 3} указывают номера функций, a и b - границы поиска корня, eps - точность\n");
        printf("--integral_test f a b eps\n f - число из диапазона {1, 2, 3} указывает номер функции, a и b - границы расчета интеграла, eps - точность\n");
    }
    else if(argc == 2)
    {
        if (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-R") == 0)
        {
             printf("\n");
            printf("Координаты пересечения функций f1 и f2: %lf\n", answerf1f2);
            printf("Координаты пересечения функций f2 и f3: %lf\n", answerf2f3);
            printf("Координаты пересечения функций f1 и f3: %lf\n", answerf1f3);
        }
        else if (strcmp(argv[1], "--integral") == 0 || strcmp(argv[1], "-I") == 0)
        {
            double square = fabs(integral(f1, answerf1f3, answerf1f2, eps2) - integral(f2, answerf1f3, answerf2f3, eps2) - integral(f3, answerf2f3, answerf1f2, eps2));
            printf("\n");
            printf("Искомая площадь области ограниченной функциями равна: %lf\n", square);
        }
        else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки");
    }
    else if(argc == 7)
    {
        if (strcmp(argv[1], "--root_test") == 0)
        {
            char *q;
            int func1 = atoi(argv[2]);
            int func2 = atoi(argv[3]);
            double a = strtod(argv[4], &q);
            double b = strtod(argv[5], &q);
            double eps = strtod(argv[6], &q);
            if ((func1 == 1 && func2 == 2) || (func2 == 1 && func1 == 2)) printf("%f",root(f1, f1pr, f2, f2pr, a, b, eps));
            else if ((func1 == 1 && func2 == 3) || (func2 == 1 && func1 == 3)) printf("%f",root(f1, f1pr, f3, f3pr, a, b, eps));
            else if ((func1 == 3 && func2 == 2) || (func2 == 3 && func1 == 2)) printf("%f",root(f2, f2pr, f3, f3pr, a, b, eps));
            else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки");
        }
        else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки");
    }
    else if(argc == 6)
    {   
        if (strcmp(argv[1], "--integral_test") == 0)
        {
            char *q;
            int f = atoi(argv[2]);
            double a = strtod(argv[3], &q);
            double b = strtod(argv[4], &q);
            double eps = strtod(argv[5], &q);
            if (f == 1) printf("%f", integral(f1, a, b, eps));
            else if (f == 2) printf("\n%f", integral(f2, a, b, eps));
            else if (f == 3) printf("\n%f", integral(f3, a, b, eps));
            else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки");  
        }
        else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки"); 
    }
    else printf("\nНекорректный ввод, запустите программу с ключом --help или -H для справки");  
    return 0;
}