// depends on modint

namespace comb {
    vector<mint> fac, finv, inv;
}

void cominit(int n) {
    if(!comb::fac.empty()) return;
    n = max(n + 1, 3);
    comb::fac.resize(n);
    comb::finv.resize(n);
    comb::inv.resize(n);
    comb::fac[0] = 1;
    for(int i = 1; i < n; i ++) {
        comb::fac[i] = comb::fac[i - 1] * i;
    }
    comb::finv[n - 1] = comb::fac[n - 1].inv();
    for(int i = n - 2; i >= 0; i --) {
        comb::finv[i] = comb::finv[i + 1] * (i + 1);
        comb::inv[i + 1] = comb::finv[i + 1] * comb::fac[i];
    }
}

mint com(int n, int k) {
    if(n < k || n < 0 || k < 0) return 0;
    return comb::fac[n] * comb::finv[k] * comb::finv[n - k];
}

mint H(int n, int k) {
    if(n == 0 and k == 0) return 1;
    return com(n + k - 1, k);
}