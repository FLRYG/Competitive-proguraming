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
#define rep(i, n) for (int i = 0; i < n; i++)
#define repn(i, n) for (int i = 1; i <= n; i++)
#define repr(e, x) for (auto& e : x)
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int N,K;
int A[100000];
ll B[100000];

int main() {
    cin>>N>>K;
    rep(i,N) cin>>A[i]>>B[i];
    // cout<<bitset<8>(K)<<endl;

    ll ans=0;
    rep(i,30) if(K>>i&1){
        int k=(K^(1<<i))|((1<<i)-1);
        // cout<<bitset<8>(k)<<endl;
        ll res=0;
        rep(j,N) if(((k|A[j])^k)==0) res+=B[j];
        ans=max(ans,res);
    }
    ll res=0;
    rep(j,N) if(((K|A[j])^K)==0) res+=B[j];
    ans=max(ans,res);

    cout<<ans<<endl;
    
    return 0;
}