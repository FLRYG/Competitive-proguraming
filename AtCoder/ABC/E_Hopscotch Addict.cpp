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
ll const MOD = 1000000007;

int N, M, S, T;

int main() {
    cin >> N >> M;
    vector<vector<int>> G(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }
    cin >> S >> T;
    S--, T--;

    vector<int> cost(3 * N, INF);
    queue<P> q;
    q.push({S, 0});
    while (!q.empty()) {
        P p = q.front();
        q.pop();
        int v = p.first;
        int c = p.second;
        if (c >= cost[c % 3 * N + v]) continue;
        cost[c % 3 * N + v] = c;
        int cnt = (c % 3 + 1) % 3 * N;
        repr(e, G[v]) {
            if (c + 1 < cost[cnt + e]) q.push({e, c + 1});
        }
    }
    // rep(i, N) {
    //     printf("%d: %d, %d, %d\n", i + 1, cost[i], cost[N + i],
    //            cost[2 * N + i]);
    // }

    int ans = cost[T] / 3;
    if (ans == INF / 3) ans = -1;

    cout << ans << endl;

    return 0;
}