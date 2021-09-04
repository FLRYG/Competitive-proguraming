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

int N;
string S;
ll C[3000];
ll D[3000];

int main() {
    cin >> N >> S;
    rep(i, N) cin >> C[i];
    rep(i, N) cin >> D[i];

    vector<vector<ll>> dp(N + 1, vector<ll>(N + 1, LINF));
    dp[0][0] = 0;
    rep(i, N) for (int j = 0; j <= i; j++) {
        if (S[i] == '(') {
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
            if (j > 0)
                dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j] + C[i]);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + D[i]);
        } else {
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + C[i]);
            if (j > 0) dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j]);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + D[i]);
        }
    }

    cout << dp[N][0] << endl;

    return 0;
}