//shinchan自作
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
