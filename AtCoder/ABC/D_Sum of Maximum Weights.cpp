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
typedef pair<ll, ll> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

struct unionFind {
    int n;
    vector<int> par;    //親
    vector<int> rank;   //木の深さ
    vector<int> scale;  //木のサイズ
    int quantity;       //木の個数
    unionFind(int _n) : n(_n) {
        par.resize(n);
        rank.resize(n);
        scale.resize(n);
        quantity = n;
        for (int i = 0; i < n; i++) {
            par[i] = i;
            rank[i] = 0;
            scale[i] = 1;
        }
    };
    ~unionFind() {}
    //木の根を求める
    int find(int x) {
        if (par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    // xとyの属する集合を併合
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        quantity--;
        if (rank[x] < rank[y]) {
            par[x] = y;
            scale[y] += scale[x];
        } else {
            par[y] = x;
            scale[x] += scale[y];
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    // xとyが同じ集合に属するか否か
    bool same(int x, int y) { return find(x) == find(y); }
    // xの属する集合のサイズ
    int size(int x) { return scale[find(x)]; }
    //木の個数
    int count() { return quantity; }
};

int N;
int u[100000];
int v[100000];
ll w[100000];

int main() {
    cin >> N;
    rep(i, N - 1) cin >> u[i] >> v[i] >> w[i];
    rep(i, N - 1) u[i]--, v[i]--;

    vector<int> id(N - 1);
    iota(all(id), 0);
    sort(all(id), [&](int i, int j) { return w[i] < w[j]; });

    ll ans = 0;
    unionFind uf(N);
    rep(i, N - 1) {
        int x = u[id[i]];
        int y = v[id[i]];
        ans += w[id[i]] * uf.size(x) * uf.size(y);
        uf.unite(x, y);
    }

    cout << ans << endl;

    return 0;
}
