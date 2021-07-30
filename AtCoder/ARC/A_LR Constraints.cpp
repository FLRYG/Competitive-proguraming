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
ll const MOD=998244353;

ll N,K;
char c[1000];
ll k[1000];

int main(){
    cin>>N>>K;
    rep(i,K) cin>>c[i]>>k[i];

    vector<ll> chk(N+1,0), cnt(N+1,0);
    rep(i,K){
        chk[k[i]]=1;
        cnt[k[i]]=1;
    }

    rep(i,K){
        if(c[i]=='L'){
            for(int j=k[i];j<=N;j++) if(!chk[j]) cnt[j]++;
        }else{
            for(int j=k[i];j>=0;j--) if(!chk[j]) cnt[j]++;
        }
    }

    ll ans=1;
    repn(i,N){
        ans*=cnt[i];
        ans%=MOD;
    }

    cout<<ans<<endl;
    
    return 0;
}