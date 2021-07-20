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
#define rep(i,n) for(ll i=0;i<n;i++)
#define repn(i,n) for(ll i=1;i<=n;i++)
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

template<class T>T gcd(T a, T b){return b?gcd(b,a%b):a;}
template<class T>T lcm(T a, T b){return a/gcd(a,b)*b;}

ll N,M;

int main(){
    cin>>N>>M;
    vector<ll> A(M),C(M);
    rep(i,M) cin>>A[i]>>C[i];

    rep(i,M) if(N-A[i]<A[i]) A[i]=N-A[i];

    map<ll,ll> m;
    rep(i,M){
        if(m[A[i]]==0) m[A[i]]=C[i];
        else m[A[i]]=min(m[A[i]],C[i]);
    }

    ll ans=LINF;
    map<ll,ll> m2;
    repr(e,m){
        if(gcd(e.first,N)==1) ans=min(ans,(N-1)*e.second);
    }

    repr(e,m2) repr(f,m2){
        if(N%(e.first*f.second)==0 && e.first%f.first==0 && f.first%e.first==0){
            ll x=e.second*(N-1)*e.first+f.second*(e.first-1);
            ans=min(ans,x);
        }
    }

    if(ans==LINF) ans=-1;

    cout<<ans<<endl;
    
    return 0;
}