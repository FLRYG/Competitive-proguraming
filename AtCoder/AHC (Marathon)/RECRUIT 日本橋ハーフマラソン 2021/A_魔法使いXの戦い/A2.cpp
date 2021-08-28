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

bool LOCAL_TEST = false;

int N, M, K;
P A[300];

int computeScore() {
    double scr = 0.0, logK = log2(K);
    repr(e, A) { scr += logK - log2(e.first + 1); }
    return (int)ceil(scr);
}

int main() {
    cin >> N >> M >> K;
    rep(i, N) cin >> A[i].first;
    rep(i, N) A[i].second = i;

    bool fl=true;
    int m = M;
    vector<P> ans;
    ans.reserve(M);
    while(m>0 && fl){
        sort(A, A + N);
        if (A[N - 1].first == 0) break;

        fl=false;
        rep(i, N) {
            int cnt = (K - A[i].first - 1) / A[N - 1].first;
            int val;
            if (cnt + 1 <= m) {
                val = A[i].first + cnt * A[N - 1].first;
                int l = -1, r = N - 1;
                while (r - l > 1) {
                    int mid = (l + r) / 2;
                    if (A[mid].first >= K - val)
                        r = mid;
                    else
                        l = mid;
                }
                val = (val + A[r].first) % K;

                if (A[i].first > val) {
                    if (LOCAL_TEST) {
                        printf("%d: (%d+%d*%d+%d)%K=%d, m=%d\n", i, A[i].first,
                            A[N - 1].first, cnt, A[r].first, val, m-cnt-1);
                    }
                    rep(j, cnt) ans.push_back({A[i].second, A[N - 1].second});
                    ans.push_back({A[i].second, A[r].second});
                    A[i].first = val;
                    m -= cnt + 1;
                    fl=true;
                }
            }
        }
    }

    repr(e, ans) cout << e.first << ' ' << e.second << endl;
    if (LOCAL_TEST) cout << computeScore() << endl;

    return 0;
}