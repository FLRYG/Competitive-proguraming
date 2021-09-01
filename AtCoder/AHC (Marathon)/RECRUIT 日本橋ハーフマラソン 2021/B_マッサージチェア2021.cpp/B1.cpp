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
typedef pair<int, int> Pa;
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

// タイマー(秒)
struct Timer {
    long long int starttime;
    Timer() {}
    ~Timer() {}

   private:
    inline long long int nowTime() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(
                   system_clock::now().time_since_epoch())
            .count();
    }

   public:
    inline void start() { starttime = nowTime(); }
    inline double getTime() { return (nowTime() - starttime) / 1e9; }
};

#define LOCALTEST 1
const double NAPIER = 2.718281828459045;
const double TIME_LIMIT = 1.98;
const double TEMPERATURE0 = 1000.0;
const double TEMPERATURE1 = 10.0;
Random_double RAND_DOUBLE(0, 1);
Timer TIMER;

double temperature = TEMPERATURE0;

inline void updateTemp(double nowTime) {
    nowTime /= TIME_LIMIT;
    temperature = pow(TEMPERATURE0, 1 - nowTime) * pow(TEMPERATURE1, nowTime);
}

template <class S>
bool adopt(S delta) {
    if (delta >= 0)
        return true;
    else {
        if (RAND_DOUBLE.nextDouble() <= pow(NAPIER, delta / temperature)) {
            return true;
        } else {
            return false;
        }
    }
}

typedef tuple<int, int, int> TP;

int N;
int E[40][40];

int computeScore(vector<vector<int>>& P) {
    int scr = 0;
    rep(i, N) rep(j, N) scr += E[i][j] * P[i][j];
    return scr;
}

inline int dist(const Pa& a, const Pa& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    TIMER.start();
    cin >> N;
    rep(i, N) rep(j, N) cin >> E[i][j];

    vector<vector<int>> prob(N, vector<int>(N, 0));
    rep(i, N) rep(j, N) prob[i][j] = E[i][j] * E[i][j];
    rep(i, N) rep(j, N) {
        if (i == 0 && j == 0) continue;
        if (j == 0 && i != 0) {
            prob[i][j] += prob[i - 1][N - 1];
        } else {
            prob[i][j] += prob[i][j - 1];
        }
    }

    Random_int raPos(0, N - 1);
    Random_int raPow(1, N);
    bitset<40 * 40> chk;
    queue<TP> quPow;
    int score = 0;

    while (TIMER.getTime() <= TIME_LIMIT){
        updateTemp(TIMER.getTime());
        rep(nnn,100){
            int i = raPos.nextInt();
            int j = raPos.nextInt();
            if (chk[i * N + j] == 1) continue;

            int power = raPow.nextInt();
            bitset<40 * 40> tmp_chk = chk;
            queue<TP> tmp_quPow = quPow;
            int tmp_score = score;
            int len = tmp_quPow.size();

            rep(k, len) {
                TP e = tmp_quPow.front();
                tmp_quPow.pop();
                int d = dist({get<0>(e), get<1>(e)}, {i, j});
                if (d <= power) {
                    tmp_score -= get<2>(e) * E[get<0>(e)][get<1>(e)];
                    tmp_chk[get<0>(e) * N + get<1>(e)] = 0;
                } else if (d <= get<2>(e)) {
                    tmp_score -= get<2>(e) * E[get<0>(e)][get<1>(e)];
                    get<2>(e) = d - 1;
                    tmp_score += get<2>(e) * E[get<0>(e)][get<1>(e)];
                    tmp_quPow.push(e);
                } else {
                    tmp_quPow.push(e);
                }
            }
            tmp_score += power * E[i][j];
            tmp_quPow.push({i, j, power});
            tmp_chk[i * N + j] = 1;

            if (adopt(tmp_score - score)) {
    #if LOCALTEST
                // printf("%d -> %d\n", score, tmp_score);
    #endif
                score = tmp_score;
                quPow = tmp_quPow;
            } else {
            }
        }
    }

    vector<vector<int>> P(N, vector<int>(N, 0));
    while (quPow.size()) {
        TP e = quPow.front();
        quPow.pop();
        P[get<0>(e)][get<1>(e)] = get<2>(e);
    }

    repr(v, P) {
        repr(e, v) cout << e << ' ';
        cout << endl;
    }
#if LOCALTEST
    cout << computeScore(P) << endl;
#endif

    return 0;
}