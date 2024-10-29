#include <stdio.h>


unsigned int mx(unsigned int x1, unsigned int x2)
{
  if (x1 > x2)
  {
    return x1;
  }
  return x2;
}

unsigned int fast_pow(int a, int b, int m)
{
    if (b == 0)
    {
        return 1;
    } 
    else if (b == 1)
    {
        return a % m;
    }
    else if (b % 2 == 0)
    {
        return (fast_pow(a, b / 2, m) * fast_pow(a, b / 2, m)) % m;
    }
    else if (b % 2 == 1)
    {
        return (fast_pow(a, b - 1, m) * (a % m)) % m;
    }
    return 1;
}

unsigned int step(unsigned int a, unsigned int b, unsigned int c, unsigned int m){
    long long int res = b;
    for (int i = 1; i < c; i++)
    {
        res = res * b;
    }
    long long int answer = fast_pow(a, res, m);
    return answer % m;
}

int main (void)
{
  unsigned int a, b, c, m;
  scanf("%u %u %u %u", &a, &b, &c, &m);
  unsigned int x1 = step(a, b, c, m);
  unsigned int x2 = step(a, c, b, m);
  unsigned int x3 = step(b, a, c, m);
  unsigned int x4 = step(b, c, a, m);
  unsigned int x5 = step(c, b, a, m);
  unsigned int x6 = step(c, a, b, m);
  unsigned int answer = mx(x1, mx(x2, mx(x3, mx(x4, mx(x5, x6)))));
  printf("%u", answer);
  
}