#include<stdio.h>
#include<stdlib.h>
void S(int n, int k)
{ int *A, i, p;
 A = (int *)malloc(k*sizeof(int));
 for(i=0; i<k; i++) A[i] = i;
 while(1) {
    for(i=0; i<k; i++) printf("%d ", A[i]);
    printf("\n");
    if (A[k-1] < n-1) A[k-1]++;
    else {
      for(p=k-1; p>0; p--)
        if (A[p] - A[p-1] > 1) break;
      if (p==0) break;
      A[p-1] ++;
      for(i=p; i<k; i++) A[i] = A[i-1] + 1;
    }
 }
}
int main(void)
{
  int n, k;
  scanf("%d", &n);
  scanf("%d", &k);
  S(n, k);
}