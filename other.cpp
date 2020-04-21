/*
long long modpow(long long a, long long n) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
*/


///////// combinatison
/*
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
*/








/*
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

*/



/*RollingHash
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
*/











///////Matrix
/*
k->size
ll k,sum;
vector<vector<ll> > mul(vector<vector<ll> > v1, vector<vector<ll> > v2){
    vector<vector<ll> > res(k,vector<ll> (k));
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            sum=0;
            for(int n=0;n<k;n++){
                sum+=(v1[i][n]*v2[n][j]);
            }
            res[i][j]=sum;
        }
    }
    return res;
}

vector<vector<ll> > matpow(vector<vector<ll> > a,ll n) {
    vector<vector<ll> > res(k,vector<ll> (k,0));
    for(int i=0;i<k;i++){
        res[i][i]=1;
    }
    while(n>0) {
        if (n&1)res=mul(res,a);
        a=mul(a,a);
        n>>=1;
    }
    return res;
}
*/



////extEuclid
/*
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
*/

