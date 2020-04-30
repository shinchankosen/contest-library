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





///////modint
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%mod+mod)%mod){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, const mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}
