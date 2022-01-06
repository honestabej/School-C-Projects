#include <stdio.h>
#define addm(a,b) (a) + (b)
#define squarem(a) a * (a)
#define maxm(a,b) (a > b) ? a : b
#define evenm(a) (a % 2 == 0) ? 0 : 1

int addf(int a, int b) {
    return a + b;
}
int squaref(int a) {
    return a * a;
}
int maxf(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}
int evenf(int a) {
    if (a % 2 == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int a = 2, b = 8;
    addf(a,b); printf("addf(a,b) = %d\n", addf(a,b));
    addm(a,b); printf("addm(a,b) = %d\n", addm(a,b));
    addf(a++,b--); printf("addf(a++,b--) = %d\n", addf(a++,b--));
    a = 2; b = 8; // reset a,b values
    addm(a++,b--); printf("addm(a++,b--) = %d\n", addm(a++,b--));

    a = 2; b = 8;
    squaref(a); printf("squaref(a) = %d\n", squaref(a));
    squarem(a); printf("squarem(a) = %d\n", squarem(a));
    squaref(--a); printf("squaref(--a) = %d\n", squaref(--a));
    a = 2; b = 8;
    squarem(--a); printf("squarem(--a) = %d\n", squarem(--a));

    a = 2; b = 8;
    maxf(a,b); printf("maxf(a,b) = %d\n", maxf(a,b));
    maxm(a,b); printf("maxm(a,b) = %d\n", maxm(a,b));
    maxf(--a,--b); printf("maxf(--a,--b) = %d\n", maxf(--a,--b));
    a = 2; b = 8;
    maxm(--a,--b); printf("maxm(--a,--b) = %d\n", maxm(--a,--b));

    a = 2; b = 8;
    evenf(a); printf("evenf(a) = %d\n", evenf(a));
    evenm(a); printf("evenm(a) = %d\n", evenm(a));
    evenf(a++); printf("evenf(a++) = %d\n", evenf(a++));
    a = 2; b = 8;
    evenm(a++); printf("evenm(a++) = %d\n", evenm(a++));

    return 0;
}