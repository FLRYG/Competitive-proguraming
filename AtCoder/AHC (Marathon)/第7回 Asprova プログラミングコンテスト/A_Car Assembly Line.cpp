#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#define rep(i, n) for (int i = 0; i < n; i++)
#define repn(i, n) for (int i = 1; i <= n; i++)
#define repr(e, x) for (auto& e : x)
using namespace std;
typedef long long ll;
typedef long double ld;
// typedef pair<int,int> P;
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

const bool LOCALTEST = false;
const double E = 2.718281828459045;
const double TIME_LIMIT = 1.9;
const double TEMPERATURE0 = 1e3;
const double TEMPERATURE1 = 6e2;
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
        if (RAND_DOUBLE.nextDouble() <= pow(E, delta / temperature)) {
            return true;
        } else {
            return false;
        }
    }
}

struct Station {
    int right, left;
};

int M;  // 車の種類数 M
int S;  // 作業員の人数 S
int T;  // 車の流れる間隔 T[s]
int L;  // 一日の最大作業時間 L[s]
int t[40]
     [80];  // 車種 i の車に対する作業ステーション j での必要作業時間 t[i][j]
Station station[81];  // 作業ステーション j の大きさ [x[j-1],x[j]]
int N;                //  需要の合計
int num[40];          // 車種 i の需要 n[i]

int computeScore(int K, vector<int>& p) {
    try {
        //シミュレーション
        // Simulation

        int Time = 0;
        int stop_Time = 0;

        // index of the next task for each station(0~K-1)
        //各ステーションに対し、次に処理すべきタスクの番号(0~K-1)
        vector<int> head(S);

        // progress of for each pair of car and station
        //タスクとステーションのペアに関する進捗
        vector<vector<int> > progress(K, vector<int>(S));

        // number of completed cars of each type
        //各種類のタスクについて完了した個数
        vector<int> m(M);

        while (head[S - 1] < K) {
            // compute the minimum of these three kinds of time
            // the time when any incomplete task reaches at the end of the
            // station the time when any task reaches the beginning of the next
            // station the time when any task is completed

            //以下の中の最短時間を求める
            //未完了のタスクが未完了のままステーションの終点につく時間
            //あるタスクについて次のステーションに到着する時間
            //タスク完了する時間
            int t_min = INF;

            for (int j = 0; j < S; j++) {
                int k = head[j];
                if (k == K) continue;
                int x = Time - stop_Time - k * T;
                if (x < station[j].left) {
                    t_min = min(t_min, station[j].left - x);
                } else {
                    t_min = min(t_min, min(station[j].right - x,
                                           t[p[k]][j] - progress[k][j]));
                }
            }
            // If the time of next event is over L, then finish
            //次のイベントが L を超えているなら終了
            if (t_min + Time > L) {
                Time = L + 1;
                break;
            }
            // else process next event and time
            //そうでない時、次のイベントを処理して時間計算
            if (t_min > 0) {
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    if (x >= station[j].left) progress[k][j] += t_min;
                }
                Time += t_min;
            } else {
                int res_min = INF;
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    res_min = min(res_min, t[p[k]][j] - progress[k][j]);
                }

                if (res_min + Time > L) {
                    Time = L + 1;
                    break;
                }
                stop_Time += res_min;
                Time += res_min;
                for (int j = 0; j < S; j++) {
                    int k = head[j];
                    if (k == K) continue;
                    int x = Time - stop_Time - k * T;
                    if (x < station[j].left) continue;
                    progress[k][j] += res_min;
                    if (progress[k][j] == t[p[k]][j]) {
                        head[j]++;
                        if (j == S - 1) {
                            m[p[k]]++;
                        }
                    }
                }
            }
        }

        // compute score
        //スコア計算
        int score = 0;
        if (Time == L + 1 || K < N) {
            double sc = 0;
            for (int i = 0; i < M; i++) {
                sc += sqrt((double)m[i] / (double)num[i]);
            }
            sc *= 1000000.0;
            sc /= M;
            score = round(sc);
        } else {
            double sc = 1000000.0 * (2.0 - (double)Time / (double)L);
            score = round(sc);
        }

        // printf("IMOJUDGE<<<%d>>>\n", score);
        return score;
    } catch (logic_error e) {
        cerr << e.what() << endl;
        return 1;
    } catch (char* str) {
        cerr << "error: " << str << endl;
        return 1;
    }
    return 1;
}

void read() {
    cin >> M >> S >> T >> L;
    rep(i, M) rep(j, S) cin >> t[i][j];
    int tmp = 0;
    rep(j, S) {
        int x;
        cin >> x;
        station[j].left = tmp + 1;
        station[j].right = x;
        tmp = x;
    }
    N = 0;
    rep(i, M) {
        cin >> num[i];
        N += num[i];
    }
}

vector<int> solve() {
    vector<int> ans;
    ans.reserve(N);
    rep(i, M) rep(j, num[i]) ans.push_back(i);
    mt19937 engine(0);
    shuffle(ans.begin(), ans.end(), engine);

    int score = 0, tmp_score = 0;

    int loop = 0;
    while (TIMER.getTime() < TIME_LIMIT) {
        vector<int> tmp_tasks = ans;
        tmp_score = computeScore(N, tmp_tasks);
        if (score < tmp_score) {
            score = tmp_score;
            ans = tmp_tasks;
        }
        loop++;
    }

    if (LOCALTEST) cout << "loop = " << loop << endl;

    return ans;
}

int main() {
    TIMER.start();
    read();

    vector<int> ans = solve();

    cout << ans.size() << endl;
    repr(e, ans) cout << e + 1 << ' ';
    cout << endl;

    if (LOCALTEST) cout << computeScore(ans.size(), ans) << endl;

    return 0;
}