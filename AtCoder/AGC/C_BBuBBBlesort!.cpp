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
// typedef pair<ll, ll> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int N;

int main() {
    cin >> N;
    vector<int> A(N), id(N), B, C;
    rep(i, N) cin >> A[i];

    iota(all(id), 0);
    sort(all(id), [&](int i, int j) { return A[i] < A[j]; });
    rep(i, N) A[id[i]] = i;

    int ans = 0;
    for (int i = 0; i < N; i += 2) {
        if (A[i] & 1) ans++;
    }

    cout << ans << endl;

    return 0;
}