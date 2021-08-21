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

template <typename T>
vector<T> smallest_prime_factors(T n) {
    vector<T> spf(n + 1);
    for (int i = 0; i <= n; i++) spf[i] = i;

    for (T i = 2; i * i <= n; i++) {
        // 素数だったら
        if (spf[i] == i) {
            for (T j = i * i; j <= n; j += i) {
                // iを持つ整数かつまだ素数が決まっていないなら
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    return spf;
}

int N, M;
int A[100000];

int main() {
    cin >> N >> M;
    rep(i, N) cin >> A[i];

    vector<int> spf = smallest_prime_factors(100000);

    set<int> se;
    rep(i, N) {
        int x = A[i];
        while (x != 1) {
            se.insert(spf[x]);
            x /= spf[x];
        }
    }

    vector<int> ans;
    repn(k, M) {
        int K = k, fl = true;
        while (K != 1) {
            if (se.find(spf[K]) != se.end()) fl = false;
            K /= spf[K];
        }
        if (fl) {
            ans.push_back(k);
        }
    }

    cout << ans.size() << endl;
    repr(e, ans) cout << e << endl;

    return 0;
}