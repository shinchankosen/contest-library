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
