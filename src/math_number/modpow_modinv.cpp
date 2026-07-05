long long modinv(long long a, long long MOD) {
    long long b = MOD, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; std::swap(a, b);
        u -= t * v; std::swap(u, v);
    }
    u %= MOD; 
    if (u < 0) u += MOD;
    return u;
}

long long modpow(long long a, long long n, long long MOD) {
    long long res = 1;
    a %= MOD;
    if(n < 0) {
        n = -n;
        a = modinv(a, MOD);
    }
    while (n > 0) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}