// floor(sqrt(n))
long long sqrtll(long long n) { 
    // 3037000500 = ceil(sqrt(2^63))
    long long le = 0, ri = 3037000500; 
    while(ri - le > 1) {
        long long mid = (le + ri) / 2;
        if(mid * mid <= n) le = mid;
        else ri = mid;
    }
    return le;
}