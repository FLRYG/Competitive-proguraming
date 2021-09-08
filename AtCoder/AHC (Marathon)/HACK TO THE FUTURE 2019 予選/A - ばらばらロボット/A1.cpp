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

const double NAPIER = 2.718281828459045;
const double TIME_LIMIT = 2.98;
const double TEMPERATURE0 = 1e3;
const double TEMPERATURE1 = 20;
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

#define LOCALTEST 1
int loopCount = 0;

int const I[] = {1, 0, -1, 0};
int const J[] = {0, 1, 0, -1};

int N, M, L;
string S[500];
set<int> passed[29][29];

void simulate(int &i, int &j, int const k, vector<string> const &G,
              int const fl) {
    int d = 2;
    if (fl == 1)
        passed[i][j].insert(k);
    else if (fl == 0)
        passed[i][j].erase(k);
    rep(l, L) {
        int cnt = 1;
        if (G[i][j] == 'D')
            cnt = 2;
        else if (G[i][j] == 'T')
            cnt = 3;
        if (S[k][l] == 'S') {
            rep(n, cnt) {
                int x = i + I[d];
                int y = j + J[d];
                if (0 <= x && x < M && 0 <= y && y < M && G[x][y] != '#') {
                    i = x;
                    j = y;
                }
            }
            if (fl == 1)
                passed[i][j].insert(k);
            else if (fl == 0)
                passed[i][j].erase(k);
        } else if (S[k][l] == 'L') {
            if (G[i][j] == 'R') {
                d = (d + 3) % 4;
            } else {
                d = (d + cnt) % 4;
            }
        } else {
            if (G[i][j] == 'L') {
                d = (d + 1) % 4;
            } else {
                d = (d + cnt * 3) % 4;
            }
        }
    }
}

int main() {
    TIMER.start();
    cin >> N >> M >> L;
    rep(i, N) cin >> S[i];

    vector<string> G(M, string(M, '.'));
    rep(j, M) G[0][j] = '#';
    repn(i, M - 2) {
        G[i][0] = '#';
        G[i][M - 1] = '#';
    }
    rep(j, M) G[M - 1][j] = '#';

    vector<vector<int>> goalG(M, vector<int>(M, 0));
    vector<int> goalN(N);
    rep(k, N) {
        int i = 14, j = 14;
        simulate(i, j, k, G, 1);
        goalG[i][j]++;
        goalN[k] = i * M + j;
    }

    int score = 0;
    rep(i, M) rep(j, M) {
        if (goalG[i][j] == 1)
            score += 10;
        else if (goalG[i][j] == 2)
            score += 3;
        else if (goalG[i][j] == 3)
            score += 1;
    }

    Random_int raPos(1, M - 2);
    Random_int raEff(0, 5);
    string EFF = ".DTLR#";
    while (TIMER.getTime() < TIME_LIMIT) {
        updateTemp(TIMER.getTime());
        rep(nnn, 10) {
#if LOCALTEST
            loopCount++;
#endif
            int i = raPos.nextInt();
            int j = raPos.nextInt();
            int eff = raEff.nextInt();

            char ori_eff = G[i][j];
            if (EFF[eff] == ori_eff) continue;
            G[i][j] = EFF[eff];

            int tmp_score = score;
            map<int, int> tmp_goalG;
            repr(k, passed[i][j]) {
                int x = goalN[k] / M;
                int y = goalN[k] % M;
                int &cnt = tmp_goalG[goalN[k]];
                cnt--;
                if (cnt + goalG[x][y] == 0)
                    tmp_score -= 10;
                else if (cnt + goalG[x][y] == 1)
                    tmp_score += 7;
                else if (cnt + goalG[x][y] == 2)
                    tmp_score += 2;
                else if (cnt + goalG[x][y] == 3)
                    tmp_score += 1;

                x = 14, y = 14;
                simulate(x, y, k, G, -1);
                cnt = tmp_goalG[x * M + y];
                cnt++;
                if (cnt + goalG[x][y] == 1)
                    tmp_score += 10;
                else if (cnt + goalG[x][y] == 2)
                    tmp_score -= 7;
                else if (cnt + goalG[x][y] == 3)
                    tmp_score -= 2;
                else
                    tmp_score -= 1;
            }

            if (adopt(tmp_score - score)) {
                score = tmp_score;
                repr(e, tmp_goalG) {
                    goalG[e.first / M][e.first % M] += e.second;
                }
                G[i][j] = ori_eff;
                set<int> tmp_passed = passed[i][j];
                repr(k, tmp_passed) {
                    int x = 14, y = 14;
                    simulate(x, y, k, G, 0);
                }
                G[i][j] = EFF[eff];
                repr(k, tmp_passed) {
                    int x = 14, y = 14;
                    simulate(x, y, k, G, 1);
                    goalN[k] = x * M + y;
                }
            } else {
                G[i][j] = ori_eff;
            }
        }
    }

    repr(e, G) cout << e << "\r\n";
#if LOCALTEST
    cout << "loopCount: " << loopCount << endl;
    cout << "score: " << score << endl;
#endif

    return 0;
}