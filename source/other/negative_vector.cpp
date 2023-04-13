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
