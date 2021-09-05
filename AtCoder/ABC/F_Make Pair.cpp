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
ll const MOD = 998244353;

// 前計算あり
const int MAX = 510000;
ll fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算
ll COM(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

int N, M;
int G[400][400];

int main() {
    COMinit();
    cin >> N >> M;
    rep(i, M) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a][b] = 1;
        G[b][a] = 1;
    }

    vector<vector<ll>> dp(2 * N, vector<ll>(2 * N));
    rep(i, 2 * N - 1) dp[i][i + 1] = G[i][i + 1];
    for (int k = 2; k <= 2 * N; k += 2) {
        for (int l = 0; l + k - 1 < 2 * N; l += 2) {
            int r = l + k - 1;
            if (G[l][r] && k > 2) dp[l][r] += dp[l + 1][r - 1];
            for (int i = l + 1; i + 1 < r; i++) {
                dp[l][r] += dp[l][i] * dp[i + 1][r] % MOD * 2;
                dp[l][r] += COM(dp[l][i] + dp[i + 1][r]) dp[l][r] %= MOD;
            }
            // cout<<l<<' '<<r<<' '<<dp[l][r]<<endl;
        }
    }

    for (int r = 1; r <= 2 * N; r++) {
        for (int l = !(r&1); l < r; l += 2) {
            for(int k =)
        }
    }

    cout << dp[0][2 * N - 1] << endl;

    return 0;
}

// #include <stdio.h>
//
// #include <algorithm>
// #include <bitset>
// #include <chrono>
// #include <cmath>
// #include <deque>
// #include <functional>
// #include <iomanip>
// #include <iostream>
// #include <list>
// #include <map>
// #include <queue>
// #include <random>
// #include <set>
// #include <stack>
// #include <string>
// #include <unordered_map>
// #include <vector>
// #define rep(i, n) for (int i = 0; i < n; i++)
// #define repn(i, n) for (int i = 1; i <= n; i++)
// #define repr(e, x) for (auto& e : x)
// #define all(x) (x).begin(), (x).end()
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// // typedef pair<int, int> P;
// // typedef pair<int,P> IP;
// // typedef pair<P,P> PP;
// double const PI = 3.141592653589793;
// int const INF = 1001001001;
// ll const LINF = 1001001001001001001;
// ll const MOD = 998244353;

// int N,M;
// int G[400][400];

// ll dp[400][400];

// ll f(int l, int r){
//     if(dp[l][r]!=-1) return dp[l][r];
//     if(l+1==r) return G[l][r];
//     ll res=0;
//     if(G[l][r]){
//         res+=f(l+1,r-1);
//         res%=MOD;
//     }
//     for(int k=l+1;k<r;k+=2){
//         res+=f(l,k)+f(k+1,r);
//         res%=MOD;
//     }
//     return res;
// }

// int main() {
//     cin>>N>>M;
//     rep(i,M){
//         int a,b;
//         cin>>a>>b;
//         a--, b--;
//         G[a][b]=1;
//         G[b][a]=1;
//     }

//     rep(i,2*N) rep(j,2*N) dp[i][j]=-1;

//     ll ans=f(0,2*N-1);
//     cout<<ans<<endl;

//     return 0;
// }