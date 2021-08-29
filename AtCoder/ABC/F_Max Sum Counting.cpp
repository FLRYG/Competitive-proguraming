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
typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 998244353;

ll N;
P AB[5001];

int main() {
    cin>>N;
    repn(i,N) cin>>AB[i].first;
    repn(i,N) cin>>AB[i].second;

    sort(AB,AB+N);

    ll ans=0;
    vector<vector<int>> dp(N+1,vector<int>(5000+1,0));
    vector<vector<int>> dp2(N+1,vector<int>(5000+1,0));
    dp[0][0]=1;
    repn(i,N){
        rep(j,5001){
            dp[i][j]=dp[i-1][j];
            if(j-AB[i].second>=0){
                dp[i][j]+=dp[i-1][j-AB[i].second];
                if(i>=2) dp[i][j]+=dp[i-2][j-AB[i].second];
                dp[i][j]%=MOD;
            }
        }
        repn(j,AB[i].first){
            ans+=dp[i][j];
            ans%=MOD;
        }
    }

    cout<<ans<<endl;
    
    return 0;
}