#include <iostream>
#include <fstream>
#include <cmath>

using ld = long double;

// Параметры двигателя
const int N = 12;//количество сечений
const ld Lambda_metal = 209.3; // Теплопроводность металла
const ld S_thermophysical = 3000.0; // Теплофизическая функция
const ld Tct = 600.0; // Относительная температура стенки
const ld Pressure = 30.0; //Давление в камере
const ld Epsillon[N] = // Эпсилон в сечениях
{1.0, 1.0, 1.0, 1.0, 0.8, 0.6, 0.5, 0.4, 0.3, 0.1, 0.05};
const ld InternalCoolingCoefficient[N] = //коэффициент внутренненого охлаждения в сечениях
{0.935, 0.935, 0.925, 0.925, 0.940, 0.940, 0.935, 0.935, 0.930, 0.930, 0.990, 0.990};

// Параметры топлива 
const ld TOG = 2100.0; // Температура газа
const ld Relative_temperature = Tct / TOG; // Относительная температура
// Физические константы
const ld Pr = 0.79; // Число Прандля
const ld K = 1700.0; // Коэффициент (какой??)
const ld B = 0.00852;

//Класс для расчета температуры
class Temp
{
public:
    ld  diameter, // диаметр
        x_step, // шаг по оси х 
        wall_thickness, // толщина стенки
        critical_diameter; // диаметр критики
    int section_number; // номер сечения

    Temp(ld dm, ld x, ld w, ld c, ld n) : diameter(dm), x_step(x), wall_thickness(w), critical_diameter(c), section_number(n){}

    ld relativeDiameter()// Относительный диаметр
    {
        return (diameter / critical_diameter); 
    }

    ld convectiveFlow() // Расчет конвективных потоков
    {   
        return (B / pow(relativeDiameter(), 1.82) * pow((Pressure * 9.81 * pow(10.0, 4.0)), 0.85)/pow((critical_diameter * pow(10.0, -3.0)), 0.15) * S_thermophysical / pow(Pr, 0.58) * pow(10.0, -6));
    }
    
    ld radiativeFlow()// Расчет лучистого потока
    {
        return (5.67 * pow((TOG/100), 4.0) * pow(10.0, -6.0) * Epsillon[section_number]);
    }

    ld totalFlow()// Расчет суммарного потока
    {
        return((radiativeFlow() + convectiveFlow()) * InternalCoolingCoefficient[section_number]);
    }


    ld finalTemperature() // Расчет температуры стенки
    {
       return((wall_thickness * pow(10.0, 3.0) * (totalFlow())) / Lambda_metal + 273.0);   
    }
    
};


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    double dm[N];//входные данные диаметра по сечениям 
    double x[N];//входные данные шага по оси х
    double w; //толщина стенки
    double c; //диаметр критики
    for (int i = 0; i < N; i++)
    {
        scanf("%Lf", &dm[i]);
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%Lf", &x[i]);
    }
    scanf("%Lf", &w);
    scanf("%Lf", &c);
    for (int i = 0; i < N; i++)
    {
        Temp t(dm[i], x[i], w, c, i);
        printf("%.3Lf\n", t.finalTemperature());
    }
}