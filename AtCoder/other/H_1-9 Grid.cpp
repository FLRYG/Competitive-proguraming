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
#define repr(e, x) for (auto &e : x)
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

struct Edge {
    int to, cost;
    Edge() : to(0), cost(0) {}
    Edge(ll _to, const ll _cost) : to(_to), cost(_cost) {}
    bool operator<(const Edge &e) const { return cost < e.cost; }
    bool operator>(const Edge &e) const { return cost > e.cost; }
    bool operator<=(const Edge &e) const { return !(cost > e.cost); }
    bool operator>=(const Edge &e) const { return !(cost < e.cost); }
};

void dijkstra(vector<vector<Edge>> &G, vector<int> &cost, int s) {
    cost.assign(G.size(), INF);
    priority_queue<Edge, vector<Edge>, greater<Edge>> que;
    que.push(Edge(s, 0));
    while (!que.empty()) {
        Edge e = que.top();
        que.pop();
        if (e.cost >= cost[e.to]) continue;
        cost[e.to] = e.cost;
        for (auto next : G[e.to]) que.push(Edge(next.to, e.cost + next.cost));
    }
}

int N, M;
string A[50];

int main() {
    cin >> N >> M;
    rep(i, N) cin >> A[i];

    int si, sj, gi, gj;
    vector<vector<P>> v(11);
    rep(i, N) rep(j, M) {
        if (A[i][j] == 'S') {
            v[0].push_back({i, j});
            si = i, sj = j;
        } else if (A[i][j] == 'G') {
            v[10].push_back({i, j});
            gi = i, gj = j;
        } else {
            v[A[i][j] - '0'].push_back({i, j});
        }
    }

    vector<vector<Edge>> G(N * M);
    rep(i, N) rep(j, M) {
        if (A[i][j] == 'S') {
            repr(e, v[1]) G[i * M + j].push_back(Edge(
                e.first * M + e.second, abs(i - e.first) + abs(j - e.second)));
        } else if (A[i][j] == 'G') {
            continue;
        } else {
            repr(e, v[A[i][j] - '0' + 1]) G[i * M + j].push_back(Edge(
                e.first * M + e.second, abs(i - e.first) + abs(j - e.second)));
        }
    }

    vector<int> cost(N * M);
    dijkstra(G, cost, si * M + sj);

    int ans = cost[gi * M + gj];
    if (ans == INF) ans = -1;

    cout << ans << endl;

    return 0;
}