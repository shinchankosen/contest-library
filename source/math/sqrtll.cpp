ll sqrtll(ll n) { 
    ll le = 0, ri = 3'000'000'001;
    while(ri - le > 1) {
        ll mid = (le + ri) / 2;
        if(mid * mid <= n) le = mid;
        else ri = mid;
    }
    return le;
}