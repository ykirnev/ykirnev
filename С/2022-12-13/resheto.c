#include <stdio.h>
#include <stdlib.h>

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int Mas[n + 1];
    for(int i = 0; i < n + 1; i++){
        Mas[i] = 1;
    }
    Mas[1] = 0;
    for(int i = 2; i < n + 1; i++){
        if(Mas[i] != 0){
            for(int j = i + i; j < n + 1; j += i){
                Mas[j] = 0;
            }
        }
    }
    int counter = 0;
    for(int i = 0; i < n + 1; i++){
        if(Mas[i]!=0 && i >= m)
        {
            printf("%d ", i);
            counter++;
        }
    }
    if (counter == 0){
        printf("%d", counter);
    }
    return 0;
}