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

ll mfrac(ll n){
    if(n==0) return 1;
    else return n*mfrac(n-1);
}

ll mperm(ll n,ll r){
    if(n>0 && r==0) return n;
    ll res=1;
    for(ll i=0;i<r;i++) res=res*(n-i);
    return res;
}

ll mcomb(ll n,ll r){
    if(r>n-r) r=n-r;
    ll res=mperm(n,r);
    return res/mfrac(r);
}

int N;
int C[100];

int main(){
    cin>>N;
    rep(i,N) cin>>C[i];

    double ans=0.0;
    rep(i,N){
        int cnt=0;
        rep(j,N){
            if(i==j) continue; 
            if(C[i]%C[j]==0) cnt++;
        }
        cout<<"i = "<<i<<endl;
        int res=0;
        for(int j=0;j<=cnt;j+=2){
            for(int k=j+1;k<=N-cnt+j;++k){
                // cout<<mcomb(cnt,j)<<endl;
                // cout<<mcomb(k-1,j)<<endl;
                // cout<<mcomb(N-k,cnt-j)<<endl;
                res+=mcomb(cnt,j)*mcomb(k-1,j)*mcomb(N-k,cnt-j);
            }
        }
        cout<<res<<endl;
        ans+=res;
    }

    repn(i,N) ans/=i;

    cout<<ans<<endl;
    
    return 0;
}