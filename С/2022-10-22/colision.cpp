#include <iostream>
#include <fstream>
#include <cmath>

using ld = long double;

const int n = 100; //размерность поля
const ld A_x = 10; //координата X разделяющей оси A
const ld A_y = 10; //координата Y разделяющей оси A
const int m = 200; //количество граней
const ld L = sqrt(A_x * A_x - A_y * A_y);//константа для нормирования координат

class P //класс полигона
{
public:
    ld coordinates[n][n],//массив координат точек объекта

    P(ld p[n][n]): coordinates(p[n][n]){}

    ld build_Face()//построение грани
    {
        ld E[m]; //массив граней
        for (int i = 0; i < m; i++)
        {
            E[i] = 0;
        }
        for (int i = 0; i < m; i++)
        {
           if ((i + 1) >= (n + 1))
           {
            for (int j = 0; j < n; j++)
            {
                E[i] = E[i] + p[0][j] - p[i][j];
            }
           }
           else
           {
            for (int j = 0; j < n; j++)
            {
                E[i] = E[i] + p[i + 1][j] - p[i][j];
            }
           }
        }
        return E[0][0];
    }
    ld min()//скалярное произведение между первой точкой объека и разделеющей осью А
    {
        ld s[n];
        ld min, max;
        s[0] = coordinates[A_x][0] * A_x + coordinates[0][A_y] * A_y;
        min = s;
        max = s   
        for (int i = 0; i < n; i ++)
        {
            s[i]= coordinates[A_x][i] * A_x + coordinates[i][A_y] * A_y;
            if (s[i] < min)
            {
                min = s[i];
            }
            if (s[i]> max)
            {
                max = s[i];
            }
        }
        return min, max;
    }

}

int main(void)
{
    freopen("input.txt", "r", stdin);
    P poligon_A, poligon_B;
    ld minA, minB, maxA, maxB;
    //тут должен быть ввод координат
    minA, maxA = poligon_A.scal();
    minB, maxB = poligon_B.scal();
    //тут надо сделать класс для дальнейших расчетов пункты 8 - 16
    
}