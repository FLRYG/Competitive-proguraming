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

// タイマー(秒)
struct Timer {
    long long int starttime;
    Timer() {}
    ~Timer() {}

private:
    inline long long int nowTime() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    }

public:
    inline void start() { starttime = nowTime(); }
    inline double getTime() { return (nowTime() - starttime) / 1e9; }
};

const double NAPIER = 2.718281828459045;
const double TIME_LIMIT = 1.48;
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
        if (RAND_DOUBLE.nextDouble() <= pow(NAPIER, delta / temperature)) {
            return true;
        } else {
            return false;
        }
    }
}

#define LOCALTEST 0

int N, K, Q;
int A[100][100];
int r[240], c[240];

int main() {
    TIMER.start();
    cin >> N >> K >> Q;
    rep(i, N) rep(j, N) cin >> A[i][j];
    rep(i, Q){
        cin >> r[i] >> c[i];
        r[i]--, c[i]--;
    }

#if LOCALTEST
    vector<vector<char>> vv(N, vector<char>(N, 'o'));
    rep(i,Q) rep(k,K){
        vv[r[i]][c[i]+k]='#';
    }
    rep(i,N){
        rep(j,N) cout<<vv[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
#endif

    Random_int ra(1,100000);
    vector<vector<int>> S(N, vector<int>(N, 0));
    rep(i,10){
        S[0][i]=1;
        S[i][N-1]=2;
        S[N-1][N-1-i]=3;
        S[N-1-i][0]=4;
    }
    while(TIMER.getTime()<=TIME_LIMIT){
        int col=ra.nextInt()%4+1;
        int len=ra.nextInt()%5+1;
        int d=ra.nextInt()%2;
        int i,j;
        if(d==0){
            i=ra.nextInt()%N;
            j=ra.nextInt()%(N-len+1);
        }else{
            i=ra.nextInt()%(N-len+1);
            j=ra.nextInt()%N;
        }
    }

    rep(i,N){
        rep(j,N) cout<<S[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}