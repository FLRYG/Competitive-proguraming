#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
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
// typedef pair<ll, ll> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

ll N,K;

int main() {
    cin>>N>>K;
    
    vector<ll> dp(N+1), dp2(N+1);
    dp2[0]=dp2[1]=1;
    for(int i=2;i<=N-1;i++){
        dp2[i]=dp2[i-1]*2%MOD;
    }
    dp2[N]=dp2[N-1];

    repn(i,N){
        if(i>=K){
            dp[i]=dp[i-1]+dp2[i-K];
            dp[i]%=MOD;
        }
        dp2[i]-=dp[i];
        dp2[i]%=MOD;
    }
    if(dp2[N]<0) dp2[N]+MOD;

    repn(i,N) cout<<dp[i]<<' '; cout<<endl;
    repn(i,N) cout<<dp2[i]<<' '; cout<<endl;

    cout<<dp2[N]<<endl;
    
    return 0;
}