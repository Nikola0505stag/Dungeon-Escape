#include "method.h"

// Имплементация на функцията за сумиране на две числа
int sum(int a, int b) {
    return a + b;
}

int pow(int a, int b) {
    int q = 1;
    for (int i = 0; i < b; i++) {
        q *= a;
    }

    return q;
}