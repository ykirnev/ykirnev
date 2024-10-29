#include <stdio.h>

double factorial(int n)
{
    double s = 1.0;
    for (double i = 1.0; i <= n; i = i + 1.0)
    {
        s = s * i;
    }
    return s;
}
double pw(double x, int n)
{
    double x_1 = x;
    for (int i = 2; i <= n; i = i + 1)
    {
        x = x * x_1;
    }
    if (n % 4 == 3)
    {
        x = x * (-1.0); 
    }
    return x;

}
int main (void)
{
    int n;
    double x, answer = 0.0;
    scanf("%lf",&x);
    scanf("%d",&n);
    n = n * 2 - 1;
    for (int i = 1; i <= n; i = i + 2)
    {
        answer = answer + pw(x,  i) / factorial(i);
    }
    printf("%.6lf\n", answer);
    return 0;
}   