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
typedef pair<int, P> IP;
typedef pair<P, P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

#define LOCALTEST 0

int const I[] = {1, 0, -1, 0};
int const J[] = {0, 1, 0, -1};
string DIRC = "DRUL";

int N, M, B;
int gx, gy;
int rx[100], ry[100], rc[100];
int bx[300], by[300];

typedef tuple<int, int, int, int> CPD;
typedef tuple<int, int, char> Out;

// 貪欲
// 合流するまでにかかる曲がる回数を小さくする
// 各頂点からスタート
// A2の改良　無駄な方向案内を減らす
int main() {
    cin >> N >> M >> B;
    cin >> gx >> gy;
    rep(i, M) {
        char c;
        cin >> rx[i] >> ry[i] >> c;
        rep(j, 4) if (DIRC[j] == c) rc[i] = j;
    }
    rep(i, B) cin >> bx[i] >> by[i];

    vector<vector<int>> G(N, vector<int>(N, 1));
    rep(i, B) G[bx[i]][by[i]] = 0;

    vector<vector<int>> dist(N, vector<int>(N, INF));
    queue<IP> q;
    q.push({0, {gx, gy}});
    while (!q.empty()) {
        IP p = q.front();
        q.pop();
        int c = p.first;
        int i = p.second.first;
        int j = p.second.second;
        if (c >= dist[i][j]) continue;
        dist[i][j] = c;
        rep(k, 4) {
            int x = (i + I[k] + N) % N;
            int y = (j + J[k] + N) % N;
            if (c + 1 < dist[x][y] && G[x][y]) q.push({c + 1, {x, y}});
        }
    }

    vector<vector<int>> R(N, vector<int>(N, -1));
    vector<vector<int>> use(N, vector<int>(N, 0));
    rep(mmm, M) {
        int gi = -1, gj, gd;
        vector<vector<vector<int>>> dist(
            N, vector<vector<int>>(N, vector<int>(4, INF)));
        vector<vector<vector<CPD>>> prev(
            N, vector<vector<CPD>>(N, vector<CPD>(4, {-1, -1, -1, -1})));
        queue<CPD> q;
        q.push({0, rx[mmm], ry[mmm], rc[mmm]});
        while (!q.empty()) {
            CPD p = q.front();
            q.pop();
            int &c = get<0>(p);
            int &i = get<1>(p);
            int &j = get<2>(p);
            int &d = get<3>(p);
            {
                int a = INF;
                CPD pre = {-1, -1, -1, -1};
                rep(k, 4) {
                    if (d == k) {
                        int x = (i + I[k ^ 2] + N) % N;
                        int y = (j + J[k ^ 2] + N) % N;
                        if (dist[x][y][d] <= a) {
                            pre = {-1, x, y, d};
                            a = dist[x][y][d];
                        }
                    } else {
                        if (dist[i][j][k] <= a) {
                            pre = {-1, i, j, k};
                            a = dist[i][j][k];
                        }
                    }
                }
                prev[i][j][d] = pre;
            }
            if ((i == gx && j == gy) || (R[i][j] != -1)) {
                gi = i;
                gj = j;
                gd = d;
                break;
            }
            if (c >= dist[i][j][d]) continue;
            dist[i][j][d] = c;
            rep(k, 4) {
                if (d == k) {
                    int x = (i + I[k] + N) % N;
                    int y = (j + J[k] + N) % N;
                    if (c < dist[x][y][d] && G[x][y]) q.push({c, x, y, d});
                } else {
                    if (c + 1 < dist[i][j][k]) q.push({c + 1, i, j, k});
                }
            }
        }
        if (gi == -1) continue;
#if LOCALTEST
        cout << "i = " << mmm << endl;
        cout << "start: " << rx[mmm] << ' ' << ry[mmm] << ' ' << DIRC[rc[mmm]]
             << endl;
        cout << "goal: " << gi << ' ' << gj << ' ' << DIRC[gd] << endl;
#endif
        if (R[gi][gj] != gd) use[gi][gj] = 1;
        while (!(gi == rx[mmm] && gj == ry[mmm] && gd == rc[mmm])) {
            CPD cpd = prev[gi][gj][gd];
            R[get<1>(cpd)][get<2>(cpd)] = gd;
            if (get<3>(cpd) != gd) use[get<1>(cpd)][get<2>(cpd)] = 1;
            gi = get<1>(cpd);
            gj = get<2>(cpd);
            gd = get<3>(cpd);
#if LOCALTEST
            cout << gi << ' ' << gj << ' ' << DIRC[gd] << endl;
#endif
        }
#if LOCALTEST
        cout << "  ";
        rep(i, N) cout << i % 10 << ' ';
        cout << endl;
        rep(i, N) {
            cout << i % 10 << ' ';
            rep(j, N) {
                if (i == gx && j == gy)
                    cout << "G ";
                else if (G[i][j] == 0)
                    cout << "# ";
                else if (use[i][j])
                    cout << DIRC[R[i][j]] << ' ';
                else if (R[i][j] != -1)
                    cout << "+ ";
                else
                    cout << '.' << ' ';
            }
            cout << i % 10 << ' ';
            cout << endl;
        }
        cout << "  ";
        rep(i, N) cout << i % 10 << ' ';
        cout << endl << endl;
#endif
    }

#if LOCALTEST
    rep(i, N) {
        rep(j, N) {
            if (i == gx && j == gy)
                cout << "G ";
            else if (G[i][j] == 0)
                cout << "# ";
            else if (R[i][j] != -1)
                cout << DIRC[R[i][j]] << ' ';
            else
                cout << '.' << ' ';
        }
        cout << endl;
    }
    cout << endl;
    rep(i, N) {
        rep(j, N) {
            if (i == gx && j == gy)
                cout << "G ";
            else if (G[i][j] == 0)
                cout << "# ";
            else if (R[i][j] != -1 && use[i][j])
                cout << DIRC[R[i][j]] << ' ';
            else
                cout << '.' << ' ';
        }
        cout << endl;
    }
    cout << endl;
#endif

    int K = 0;
    vector<Out> ans;
    rep(i, N) rep(j, N) if (use[i][j]) {
        ans.push_back({i, j, DIRC[R[i][j]]});
        K++;
    }

    cout << K << endl;
    rep(i, K) {
        printf("%d %d %c\n", get<0>(ans[i]), get<1>(ans[i]), get<2>(ans[i]));
    }

    return 0;
}