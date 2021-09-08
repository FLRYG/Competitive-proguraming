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

// 整数の乱数を[a,b]の範囲で返す
struct Random_int {
    int seed, min, max;
    mt19937 mt;
    uniform_int_distribution<int> rand;
    Random_int(int _min, int _max, int _seed = 121314)
        : min(_min), max(_max), seed(_seed) {
        mt.seed(seed);
        uniform_int_distribution<int>::param_type param(min, max);
        rand.param(param);
    }
    int nextInt() { return rand(mt); }
};

// 実数の乱数を[a,b]の範囲で返す
struct Random_double {
    int seed, min, max;
    mt19937 mt;
    uniform_real_distribution<double> rand;
    Random_double(int _min, int _max, int _seed = 121314)
        : min(_min), max(_max), seed(_seed) {
        mt.seed(seed);
        uniform_real_distribution<double>::param_type param(min, max);
        rand.param(param);
    }
    double nextDouble() { return rand(mt); }
};

struct Vegetable {
    int r, c, s, e, v;
    Vegetable(int r_, int c_, int s_, int e_, int v_)
        : r(r_), c(c_), s(s_), e(e_), v(v_) {}
};

int main(int argc, char* argv[]) {
    int N = 16;
    int M = 5000;
    int T = 1000;
    int seed;
    if (argc > 1) seed = stoi(argv[1]);

    Random_int ra_i(0, 2147483647, seed);
    Random_double ra_d(0, 1, seed);

    vector<Vegetable> veges;
    rep(i, M) {
        int R, C, S, E, V;
        bool fl = true;
        while (fl) {
            int l = ra_i.nextInt() % 21;
            S = ra_i.nextInt() % (T - l);
            E = S + l;
            double v = ra_d.nextDouble() * (1.0 + S / 100.0);
            V = floor(pow(2, v));
            R = ra_i.nextInt() % N;
            C = ra_i.nextInt() % N;
            fl = false;
            repr(e, veges) {
                if (e.r == R && e.c == C) {
                    if (e.s < S && e.e >= S) fl = true;
                    if (S < e.s && E >= e.s) fl = true;
                }
            }
        }
        veges.push_back(Vegetable(R, C, S, E, V));
    }

    sort(veges.begin(), veges.end(), [&](Vegetable a, Vegetable b) {
        if (a.s != b.s)
            return a.s < b.s;
        else if (a.r != b.r)
            return a.r < b.r;
        else
            return a.c < b.c;
    });

    cout << N << ' ' << M << ' ' << T << ' ' << endl;
    repr(e, veges) cout << e.r << ' ' << e.c << ' ' << e.s << ' ' << e.e << ' '
                        << e.v << endl;

    return 0;
}