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
int A[81][81];
int B[81][81];
bool dp[82][82][81];

int main() {
    cin >> H >> W;
    repn(i, H) repn(j, W) cin >> A[i][j];
    repn(i, H) repn(j, W) cin >> B[i][j];

    vector<vector<int>> C(H + 1, vector<int>(W + 1));
    repn(i, H) repn(j, W) C[i][j] = abs(A[i][j] - B[i][j]);

    dp[1][0][0] = 1;
    repn(i, H) repn(j, W) {
        rep(k, 81) {
            if (dp[i - 1][j][k]) {
                if (C[i][j] + k <= 80) dp[i][j][C[i][j] + k] = 1;
                dp[i][j][abs(C[i][j] - k)] = 1;
            }
            if (dp[i][j - 1][k]) {
                if (C[i][j] + k <= 80) dp[i][j][C[i][j] + k] = 1;
                dp[i][j][abs(C[i][j] - k)] = 1;
            }
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