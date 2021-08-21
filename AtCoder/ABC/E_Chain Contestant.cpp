#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#define rep(i, n) for (ll i = 0; i < n; i++)
#define repn(i, n) for (ll i = 1; i <= n; i++)
#define repr(e, x) for (auto& e : x)
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<ll, ll> P;
// typedef pair<ll,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
ll const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 998244353;

ll mpow(ll x,ll n){
    if(n==0) return 1;
    else if(n%2) return x*mpow(x,n-1)%MOD;
    return mpow(x*x%MOD,n/2)%MOD;
}

ll N;
string S;

int main() {
    cin>>N>>S;
    
    vector<ll> C(N);
    rep(i,N) C[i]=S[i]-'A';

    ll ans=0;
    repn(i,(1<<10)-1){
        vector<ll> v;
        rep(j,N) if(i>>C[j]&1){
            v.push_back(C[j]);
        }
        if(v.size()==0) continue;
        vector<ll> cnt(10,0);
        ll val=v[0];
        int j=0;
        while(j<v.size()){
            ll tmp=0;
            while(j<v.size() && v[j]==val){
                // cout<<j<<' '<<val<<endl;
                j++, tmp++;
            }
            cnt[val]+=mpow(2,tmp)-1;
            cnt[val]%=MOD;
            if(j<v.size()) val=v[j];
        }
        ll res=1;
        rep(j,10){
            if(i>>j&1){
                // cout<<cnt[j]<<' ';
                res*=cnt[j];
                res%=MOD;
            }
        }
        // cout<<endl;
        ans+=res;
        ans%=MOD;
        // rep(j,10) if(i>>j&1) cout<<char('A'+j);
        // cout<<endl;
        // repr(e,v) cout<<e<<' ';
        // cout<<endl;
        // rep(j,10) if(i>>j&1) cout<<cnt[j]<<' ';
        // cout<<endl;
        // cout<<res<<endl<<endl;
    }

    cout<<ans<<endl;
    
    return 0;
}