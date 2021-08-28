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

int H, W;
int A[80][80];
int B[80][80];
bitset<160 * 80 * 2> dp[80][80];

int main() {
    cin >> H >> W;
    rep(i, H) rep(j, W) cin >> A[i][j];
    rep(i, H) rep(j, W) cin >> B[i][j];

    vector<vector<int>> C(H + 1, vector<int>(W + 1));
    rep(i, H) rep(j, W) C[i][j] = abs(A[i][j] - B[i][j]);

    int D = 159 * 80;
    dp[0][0][D - C[0][0]] = 1;
    dp[0][0][D + C[0][0]] = 1;
    rep(i, H) rep(j, W) {
        if (i) {
            dp[i][j] |= dp[i - 1][j] << C[i][j];
            dp[i][j] |= dp[i - 1][j] >> C[i][j];
        }
        if (j) {
            dp[i][j] |= dp[i][j - 1] << C[i][j];
            dp[i][j] |= dp[i][j - 1] >> C[i][j];
        }
        // cout<<i<<','<<j<<": ";
        // repr(e,s) cout<<e<<' ';
        // cout<<endl;
    }

    int ans;
    rep(k, 81) if (dp[H][W][k]) {
        ans = k;
        break;
    }
    cout << ans << endl;

    return 0;
}