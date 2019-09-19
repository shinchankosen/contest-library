#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod=1000000007;

ll modpow(ll a,ll n){
    ll res=1;
    while(n>0){
        if(n&1)res = res*a % mod;
        a = a*a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    ll M,ans=1;
    cin>>M;
    ll p,a;
    for(int i=0;i<M;i++){
        cin>>p>>a;
        p%=mod;
        if(p==1) ans*= a % mod;
        else ans*=(modpow(p,a)-1)*modpow(p-1,mod-2) % mod;
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}

