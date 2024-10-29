#include <stdio.h>


int schet(int n) {
    int kol = 0;
    if (n / 10 == 0)
        return 1;
    else {
        while (n > 0) {
            n = n / 10;
            kol += 1;
        }
        return kol;
    }
}

long int step(int b) {
    long int a = 10;
    for (int i = 1; i < b; i++) {
        a *= 10;
    }
    return a;
}

int main(void) {
    long int n, a, x1, sc;
    int arr[2010];
    for (int i = 0; i < 2010; i++){
    arr[i] = 0;
    }
    scanf("%ld %ld", &n, &a);
    sc = schet(a);
    if (a > 2010){
    printf("NO");
    return 0;
    }
    if (sc % 2 == 0){
        if (a % (step(sc / 2)) != a / (step(sc / 2))){
            printf("NO");
            return 0;
        }
    }
    x1 = n;
    for (int i = 0; i < 2012; i++){
        x1 = x1 * (step(schet(x1)) + 1) % 2010;
        arr[x1] += 1;
    }
    for (int i = 0; i < 2010; i++){
        if (arr[i] >= 2){
            printf("NO");
            return 0;
            }
        else{
        printf("YES");
        return 0;
        }
    }
}