long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}



/// modpow
long long modpow(long long a, long long n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}


///////// combinatison
ll fac[200007],finv[200007],inv[200007];
void cominit(){
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[1]=1;
    for(int i=2;i<200007;i++){
        fac[i]=fac[i-1]*i%mod;
        inv[i]=mod-inv[mod%i]*(mod/i)%mod;
        finv[i]=finv[i-1]*inv[i]%mod;
    }
}
ll com(ll n,ll k){
    if(n<k)return 0;
    if(n<0 || k<0)return 0;
    return fac[n]*(finv[k]*finv[n-k]%mod)%mod;
}
main-> cominit();








{
//Z-algorithm
    vector<int> Z(S.size());
    Z[0] = S.size();
    int i = 1, j = 0;
    while(i < S.size()){
        while(i + j < S.size() && S[j] == S[i + j]) j++;
        Z[i] = j;
        if(j == 0) { i++; continue; }
        int k = 1;
        while(i + k < S.size() && k + Z[k] < j){
            Z[i + k] = Z[k];
            k++;
        }
        i += k; j -= k;
    }
}



//// RollingHash
struct RollingHash {
    static const int base1 = 1007, base2 = 2009;
    static const int mod1 = 1000000007, mod2 = 1000000009;
    vector<long long> hash1, hash2, power1, power2;
 
    // construct
    RollingHash(const string &S) {
        int n = (int)S.size();
        hash1.assign(n+1, 0);
        hash2.assign(n+1, 0);
        power1.assign(n+1, 1);
        power2.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            hash1[i+1] = (hash1[i] * base1 + S[i]) % mod1;
            hash2[i+1] = (hash2[i] * base2 + S[i]) % mod2;
            power1[i+1] = (power1[i] * base1) % mod1;
            power2[i+1] = (power2[i] * base2) % mod2;
        }
    }
    
    // get hash of S[left:right]
    inline pair<long long, long long> get(int l, int r) const {
        long long res1 = hash1[r] - hash1[l] * power1[r-l] % mod1;
        if (res1 < 0) res1 += mod1;
        long long res2 = hash2[r] - hash2[l] * power2[r-l] % mod2;
        if (res2 < 0) res2 += mod2;
        return {res1, res2};
    }
 
    // get lcp of S[a:] and T[b:]
    inline int getLCP(int a, int b) const {
        int len = min((int)hash1.size()-a, (int)hash1.size()-b);
        int low = -1, high = len;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (get(a, a+mid) != get(b, b+mid)) high = mid;
            else low = mid;
        }
        return low;
    }
};







///////Matrix
template<class T> struct Matrix {
    vector<vector<T> > val;
    //　縦, 横, 初期値
    Matrix(int n = 1, int m = 1, T v = 0) : val(n, vector<T>(m, v)) {}
    void init(int n, int m, T v = 0) {val.assign(n, vector<T>(m, v));}
    Matrix<T>& operator = (const Matrix<T> &A) {
        val = A.val; return *this;
    }
    size_t size() const {return val.size();}
    vector<T>& operator [] (int i) {return val[i];}
    const vector<T>& operator [] (int i) const {return val[i];}
    friend ostream& operator << (ostream& s, const Matrix<T>& M) {
        s << endl;
        for (int i = 0; i < (int)M.size(); ++i) s << M[i] << endl;
        return s;
    }
};

template<class T> Matrix<T> operator * (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), B[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < B[0].size(); ++j)
            for (int k = 0; k < B.size(); ++k)
                R[i][j] += A[i][k] * B[k][j];
    return R;
}

template<class T> Matrix<T> pow(const Matrix<T> &A, long long n) {
    Matrix<T> R(A.size(), A.size());
    auto B = A;
    for (int i = 0; i < A.size(); ++i) R[i][i] = 1;
    while (n > 0) {
        if (n & 1) R = R * B;
        B = B * B;
        n >>= 1;
    }
    return R;
}

template<class T> vector<T> operator * (const Matrix<T> &A, const vector<T> &B) {
    vector<T> v(A.size());
    for (int i = 0; i < A.size(); ++i)
        for (int k = 0; k < B.size(); ++k)
            v[i] += A[i][k] * B[k];
    return v;
}

template<class T> Matrix<T> operator + (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), A[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A[0].size(); ++j)
            R[i][j] = A[i][j] + B[i][j];
    return R;
}

template<class T> Matrix<T> operator - (const Matrix<T> &A, const Matrix<T> &B) {
    Matrix<T> R(A.size(), A[0].size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A[0].size(); ++j)
            R[i][j] = A[i][j] - B[i][j];
    return R;
}





////extEuclid
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

