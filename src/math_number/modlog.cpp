// depends on modpow and modinv
// a^x ≡ b (mod. m) となる最小の正の整数 x を求める
long long modlog(long long a, long long b, int m) {
    a %= m, b %= m;

    // calc sqrt{M}
    long long le = -1, ri = m;
    while(ri - le > 1) {
        long long mid = (le + ri) >> 1;
        if(mid * mid >= m) ri = mid;
        else le = mid;
    }
    long long sqrtM = ri;

    // {a^0, a^1, a^2, ..., a^sqrt(m)} 
    map<long long, long long> apow;
    long long r = a;
    for(long long i = 1; i < sqrtM; ++ i) {
        if(!apow.count(r)) apow[r] = i;
        (r *= a) %= m;
    }

    // check each A^p
    long long A = modpow(modinv(a, m), sqrtM, m);
    r = b;
    for (long long q = 0; q < sqrtM; ++q) {
        if (r == 1 && q > 0) return q * sqrtM;
        else if (apow.count(r)) return q * sqrtM + apow[r];
        (r *= A) %= m;
    }

    // no solutions
    return -1;
}