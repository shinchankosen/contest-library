ll ftoll(string s, ll dig){
    ll m = s.length(), id = -1;
    rep(i, m) if(s[i] == '.') id = i;
    if(id == -1) s += string(dig, '0');
    else{
        s = s.substr(0, id) + s.substr(id + 1, m - id - 1);
        s += string(dig + 1 - m + id, '0');
    }
    return stoll(s);
}

// ll(sqrt(n)) 0 <= n <= 9 * 10^18
ll sqrtll(ll n) { 
    ll le = 0, ri = 3'000'000'001;
    while(ri - le > 1) {
        ll mid = (le + ri) / 2;
        if(mid * mid <= n) le = mid;
        else ri = mid;
    }
    return le;
}


////lambda
auto f = [&](auto&& f,int x) -> int{return x;};



struct node{
    int x,y;
    // 最後のconstを忘れると"instantiated from here"というエラーが出てコンパイルできないので注意
    bool operator<( const node& right ) const {
        return x == right.x ? y < right.y : x < right.x;
    }
    node& operator+=(const node& v) { x += v.x; return *this;}
    node operator+(const node& v) const { return node(*this) += v;}
    int inner(const node& right) const { return x*right.x + y*right.y;}
};


istream& operator>>(istream& is, node& v) {
  is >> v.x >> v.y; return is;
}

/////3変数構造体
struct node{
    int x,y,z;
    bool operator<( const node& right ) const {
        if(x == right.x){
            if(y == right.y) return z < right.z;
            else return y < right.y;
        }else return x < right.x;
    }
};


////第3引数sort
bool judge( const node& left, const node& right ) {
    return left.x == right.x ? left.y < right.y : left.x < right.x;
}


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
    
    // get hash of S[left:right)
    inline pair<long long, long long> get(int l, int r) const {
        long long res1 = hash1[r] - hash1[l] * power1[r-l] % mod1;
        if (res1 < 0) res1 += mod1;
        long long res2 = hash2[r] - hash2[l] * power2[r-l] % mod2;
        if (res2 < 0) res2 += mod2;
        return {res1, res2};
    }
 
    // get lcp of S[a:) and T[b:)
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





//////negative vector
struct nev{
private:
    ll a;
    vector<ll> v;
public:
    nev(ll a, ll n = 0):a(a), v(n, 0){}
    void resize(int m) {v.resize(m);}
    void push_back(ll n) {v.push_back(n);}
    size_t size() const {return v.size();}
    ll& operator [] (int i) {return v[i - a];}
};


// Fraction
struct Fraction {
    long long x, y;
    void reduc() {
        if(y < 0) y = -y, x = -x;
        long long g = abs(__gcd(x, y));
        x /= g; y /= g;
    }
    Fraction(long long x=0, long long y=1): x(x), y(y) {reduc();}
    bool operator<( const Fraction& right ) const { return x*right.y < y*right.x; }
    bool operator>( const Fraction& right ) const { return x*right.y > y*right.x; }
    bool operator==( const Fraction& right ) const { return x == right.x && y == right.y; }
    Fraction operator-() const {return Fraction(-x, y);}
    Fraction& operator+=(const Fraction& v) { 
        x = x*v.y + y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator+(const Fraction& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const Fraction& v) { 
        x = x*v.y - y*v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator-(const Fraction& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const Fraction& v) { 
        x *= v.x;
        y *= v.y;
        reduc();
        return *this;
    }
    Fraction operator*(const Fraction& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const Fraction& v) { 
        x *= v.y;
        y *= v.x;
        reduc();
        return *this;
    }
    Fraction operator/(const Fraction& v) const { return Fraction(*this) /= v;}

    bool operator<( const int& right ) const { return x < y*right; }
    bool operator>( const int& right ) const { return x > y*right; }
    bool operator==( const int& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const int& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const int& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const int& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const int& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const int& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const int& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const int& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const int& v) const { return Fraction(*this) /= v;}

    bool operator<( const long long& right ) const { return x < y*right; }
    bool operator>( const long long& right ) const { return x > y*right; }
    bool operator==( const long long& right ) const { return x == right && y == 1; }
    Fraction& operator+=(const long long& v) { 
        x += y*v;
        return *this;
    }
    Fraction operator+(const long long& v) const { return Fraction(*this) += v;}
    Fraction& operator-=(const long long& v) { 
        x -= y*v;
        return *this;
    }
    Fraction operator-(const long long& v) const { return Fraction(*this) -= v;}
    Fraction& operator*=(const long long& v) { 
        x *= v;
        reduc();
        return *this;
    }
    Fraction operator*(const long long& v) const { return Fraction(*this) *= v;}
    Fraction& operator/=(const long long& v) {
        y *= v;
        reduc();
        return *this;
    }
    Fraction operator/(const long long& v) const { return Fraction(*this) /= v;}

    Fraction inv() const { return Fraction(y, x); }
    Fraction pow(int t) const {
        if(t < 0) return inv().pow(-t);
        Fraction a(1, 1), d = *this;
        while(t) {
            d *= d;
            if(t & 1) a *= d;
            t >>= 1;
        }
        return a;
    }
    friend ostream& operator << (ostream& os, const Fraction& v) { return os << v.x << "/" << v.y; }  
};
