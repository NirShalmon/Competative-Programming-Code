/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
#include "game.h"

long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

void init(int R, int C) {
    /* ... */
}

void update(int P, int Q, long long K) {
    /* ... */
}

long long calculate(int P, int Q, int U, int V) {
    /* ... */
    return 42;
}
