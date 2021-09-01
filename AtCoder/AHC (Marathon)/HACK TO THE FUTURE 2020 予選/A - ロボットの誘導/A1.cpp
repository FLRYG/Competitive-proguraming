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
typedef pair<int, P> IP;
typedef pair<P, P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

#define LOCALTEST 1

int const I[] = {1, 0, -1, 0};
int const J[] = {0, 1, 0, -1};
string DIRC = "DRUL";

int N, M, B;
int gx, gy;
int rx[100], ry[100];
char rc[100];
int bx[300], by[300];

typedef tuple<int, int, char> Out;

// 貪欲 ゴールからの距離でbfs
int main() {
    cin >> N >> M >> B;
    cin >> gx >> gy;
    rep(i, M) cin >> rx[i] >> ry[i] >> rc[i];
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

#if LOCALTEST
    rep(i, N) {
        rep(j, N) cout << G[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    rep(i, N) {
        rep(j, N) {
            if (dist[i][j] != INF)
                cout << dist[i][j] << ' ';
            else
                cout << -1 << ' ';
        }
        cout << endl;
    }
    cout << endl;
#endif

    int K = 0;
    vector<Out> ans;
    rep(i, N) rep(j, N) if (G[i][j]) {
        int a = -1, b = INF;
        rep(k, 4) {
            int x = (i + I[k] + N) % N;
            int y = (j + J[k] + N) % N;
            if (dist[x][y] < b) {
                a = k;
                b = dist[x][y];
            }
        }
        if (a != -1) {
            K++;
            ans.push_back({i, j, DIRC[a]});
        }
    }

#if LOCALTEST
    int cntd[4]={0,0,0,0};
    rep(i,K){
        char c=get<2>(ans[i]);
        rep(j,4) if(DIRC[j]==c) cntd[j]++;
    } 
    rep(i,4){
        cout<<DIRC[i]<<": "<<cntd[i]<<endl;
    }
    cout<<endl;
#endif

    cout << K << endl;
    rep(i, K) {
        printf("%d %d %c\n", get<0>(ans[i]), get<1>(ans[i]), get<2>(ans[i]));
    }

    

    return 0;
}