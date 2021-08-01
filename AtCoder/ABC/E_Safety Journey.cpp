#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <random>
#define rep(i,n) for(int i=0;i<n;i++)
#define repn(i,n) for(int i=1;i<=n;i++)
#define repr(e,x) for(auto& e:x)
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<int,int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

ll mpow(ll x,ll n){
    if(n==0) return 1;
    else if(n%2) return x*mpow(x,n-1)%MOD;
    return mpow(x*x%MOD,n/2)%MOD;
}

ll N,M,K;

int main(){
    cin>>N>>M>>K;
    vector<vector<ll>> G(N);
    rep(i,M){
        ll u,v;
        cin>>u>>v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rep(i,N) G[i].push_back(i);
    rep(i,N) sort(G[i].begin(),G[i].end());

    vector<ll> cnt(N,0);
    repr(e,G[0]) cnt[e]=1;
    rep(i,K-1){
        rep(j,N) repr(e,G[j]){
            cnt[e]+=cnt[j];
            cnt[e]%=MOD;
        }
    }

    ll ans=mpow(2,MOD)*K%MOD*(K-1)%MOD*(N-1)%MOD;
    ans-=cnt[0];

    cout<<
    
    return 0;
}