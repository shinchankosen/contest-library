// Bostan-Mori
// find [x^N] P(x)/Q(x), O(K log K log N)
// deg(Q(x)) = K, deg(P(x)) < K, Q[0] = 1
template <typename mint> mint BostanMori(const FPS<mint> &P, const FPS<mint> &Q, long long N) {
    assert(!P.empty() && !Q.empty());
    if (N == 0) return P[0] / Q[0];
    
    int qdeg = (int)Q.size();
    FPS<mint> P2{P}, minusQ{Q};
    P2.resize(qdeg - 1);
    for (int i = 1; i < (int)Q.size(); i += 2) minusQ[i] = -minusQ[i];
    P2 *= minusQ;
    FPS<mint> Q2 = Q * minusQ;
    FPS<mint> S(qdeg - 1), T(qdeg);
    for (int i = 0; i < (int)S.size(); ++i) {
        S[i] = (N % 2 == 0 ? P2[i * 2] : P2[i * 2 + 1]);
    }
    for (int i = 0; i < (int)T.size(); ++i) {
        T[i] = Q2[i * 2];
    }
    return BostanMori(S, T, N >> 1);
}

// find [x^[[n, n + m)] P(x)/Q(x), O(k log k log n)
template <typename mint> FPS<mint> BostanMori(FPS<mint> P, FPS<mint> Q, long long n, long long m) {
    Q.normalize();
    int d = Q.size() - 1;
    auto add = P / Q;
    P -= add * Q;
    
    if(n >= (1LL << 30)) add = FPS<mint>(1, 0);
    else add >>= n;
    
    auto rec = [&](auto& rec, FPS<mint> q, ll n) -> FPS<mint> {
        if(n <= max(1, d)) {
            q.resize(n + d);
            auto ret = inv(q);
            return FPS<mint>{ret.begin() + n, ret.end()};
        }
        FPS<mint> minus{q};
        for (int i = 1; i < (int)q.size(); i += 2) minus[i] = -minus[i];
        auto v2 = minus * q;
        FPS<mint> v(d + 1);
        for (int i = 0; i < (int)v.size(); i ++) v[i] = v2[i * 2];
        int par = (n - d) & 1;
        ll nx = (n - d + par) >> 1;
        FPS<mint> ret = rec(rec, v, nx);
        
        FPS<mint> ret2(d * 2);
        for(int i = 0; i < d; i ++) ret2[i * 2] = ret[i];
        auto f = minus * ret2;
        return FPS<mint> {f.begin() + (d - par), f.begin() + (d - par) + d};
    };
    FPS<mint> f = rec(rec, Q, n) * Q;
    f.resize(d);
    (f *= P) %= Q;
    Q.resize(m);
    f *= inv(Q);
    f += add;
    f.resize(m);
    return f; 
}
