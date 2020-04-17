//shinchan自作1

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


//shinchan自作2

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ll n,m,p;
    cin>>n>>m>>p;
    n/=m;
    ll ans=0;
    while(n){
        n/=p;
        ans+=n;
    }
    cout<<ans<<endl;
    return 0;
}
/*
f(N,1) = N! = N(N-1)(N-2)*......*1
f(N,2) = N!!=N(N-2)(N-4)*......*(1,2)
f(N,3) = N!!!=N(N-3)(N-6)*.......*(1,2,3)
f(N,M)= N!!!!..(!がM個)=N(N-M)(N-2M)*.....*(1~M)
とします。
f(N,M)をP^Xで割った商をAとする。A∈ℕをみたす最大の自然数Xを求めよ。
制約
1<=M<=N<=10^18
2<=P<=10^18
NはMの倍数
N,Mは自然数
Pは素数 
PとMは互いに素
入力
N M P
出力
X
*/



//shinchan自作3
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main() {
    ll q,a,b;
    cin>>q;
    for(int i=0;i<q;i++){
	cin>>a>>b;
	if(a==b)cout<<0<<endl;
	else if(a%b&&b%a)cout<<2<<endl;
	else cout<<1<<endl; 
    }
    return 0;
}


/*
無向グラフGに無限個の頂点1,2,3....があります。
xがyの約数のとき頂点xと頂点yは辺で結ばれています。
a_iとb_iからなるQ個のクエリが与えられるので、頂点a_iからb_iへのパスの長さを求めよ。
1<=Q<=10^5
1<=a_i<=10^18
1<=b_i<=10^18
*/
