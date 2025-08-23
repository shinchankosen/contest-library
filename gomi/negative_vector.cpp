struct nev {
private:
    long long a;
    vector<long long> v;
public:
    nev(long long a, long long n = 0):a(a), v(n, 0){}
    void resize(int m) {v.resize(m);}
    void push_back(long long n) {v.push_back(n);}
    size_t size() const {return v.size();}
    long long& operator [] (int i) {return v[i - a];}
};
