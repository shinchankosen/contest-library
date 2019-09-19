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

/*
おーじくんはクリスマスプレゼントに素因数分解の問題を与えられました。
N=Π(p[i]^a[i])=p[1]^a[1]*p[2]^a[2]*.....*p[i]^a[i]....p[M]^a[M]とします(ようするにNの素因数分解です)。
Nの約数の総和を1000000007で割った余りを求めてください。
制約
Mは1<=M<=10^6を満たす自然数
p[i]はp[i]<10^18を満たす素数
a[i]はa[i]<10^18を満たす自然数
i≠jならp[i]≠p[j]
入力
M
p[1] a[1]
p[2] a[2]
p[3] a[3]
.
.
p[M] a[M]

出力は答えを1行に
*/
