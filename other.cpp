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





/////BIT ****(1-index)****
/*
ll n,m;
ll BIT[100001];
void add(ll x,ll y){
    while(x<=n){
        BIT[x]+=y;
        x+=(x&-x);
    }
}
ll sum(ll x,ll y){
    m=0;
    x--;
    while(y>=1){
        m+=BIT[y];
        y-=(y&(-y));
    }
    while(x>=1){
        m-=BIT[x];
        x-=(x&(-x));
    }
    return m; 
}
main-> memset(BIT,0,sizeof(BIT));
*/






/////////segmenttree
/*
ll n,m,seg[400001];
void segstart(void){
    memset(seg,0,sizeof(seg));
    for(ll i=1;;i*=2){
        if(n<=i){m=i;break;}
    }
    m--;n+=m;

    //for(ll i=m;i<n;i++)cin>>seg[i];
    for(int i=m-1;i>=0;i--){
        seg[i]=min(seg[2*i+1],seg[2*i+2]);
    }

}
void update(ll a,ll b){
    a+=m;seg[a]=b;
    while(a){
        a=(a-1)/2;
        seg[a]=min(seg[2*a+1],seg[2*a+2]);
    }
}
ll ans(ll a,ll b){
    ll ret=1e18;a+=m;b+=m;
    while(1){
        if(a==b){
            ret=min(ret,seg[a]);
            break;
        }
        if(b==a+1){
            ret=min(ret,seg[a]);
            ret=min(ret,seg[b]);
            break;
        }
        if(a%2)a/=2;
        else{
            ret=min(ret,seg[a]);
            a/=2;
        }
        if(b%2){
            ret=min(ret,seg[b]);
            b/=2;b--;
        }
        else{b/=2;b--;}
    }
    return ret;
}

main-> cin>>n -> segstart();

max<->min
memset
ans.ret

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

