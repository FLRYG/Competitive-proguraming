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


// 整数の乱数を[a,b]の範囲で返す
struct Random_int{
    int seed, min, max;
    mt19937 mt;
    uniform_int_distribution<int> rand;
    Random_int(int _min, int _max,int _seed=121314): min(_min),max(_max),seed(_seed){
        mt.seed(seed);
        uniform_int_distribution<int>::param_type param(min,max);
        rand.param(param);
    }
    int nextInt(){
        return rand(mt);
    }
};

// 実数の乱数を[a,b]の範囲で返す
struct Random_double{
    int seed, min, max;
    mt19937 mt;
    uniform_real_distribution<double> rand;
    Random_double(int _min, int _max,int _seed=121314): min(_min),max(_max),seed(_seed){
        mt.seed(seed);
        uniform_real_distribution<double>::param_type param(min,max);
        rand.param(param);
    }
    double nextDouble(){
        return rand(mt);
    }
};

// タイマー(秒)
struct Timer{
    long long int starttime;
    Timer(){}
    ~Timer(){}
    private:
    inline long long int nowTime() {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    }
    public:
    inline void start(){
        starttime=nowTime();
    }
    inline double getTime(){
        return (nowTime()-starttime)/1e9;
    }
};

const bool LOCALTEST=true;
const double E=2.718281828459045;
const double TIME_LIMIT=1.9;
const double TEMPERATURE0=10;
const double TEMPERATURE1=6;
Random_double RAND_DOUBLE(0,1);
Timer TIMER;

double temperature=TEMPERATURE0;

inline void updateTemp(double nowTime){
    nowTime/=TIME_LIMIT;
    temperature=pow(TEMPERATURE0,1-nowTime)*pow(TEMPERATURE1,nowTime);
}

template<class S> bool adopt(S delta){
    if(delta>=0) return true;
    else{
        if(RAND_DOUBLE.nextDouble()<=pow(E,delta/temperature)){
            return true;
        }else{
            return false;
        }
    }
}

int N,M,K;
vector<int> A(300);

int computeScore(vector<P> &ans){
    vector<int> a=A;
    repr(e,ans){
        a[e.first]=(a[e.first]+a[e.second])%K;
    }
    double scr=0.0, logK=log2(K);
    repr(e,a){
        scr+=logK-log2(e+1);
    }
    return (int)ceil(scr);
}

int main() {
    TIMER.start();
    cin>>N>>M>>K;
    rep(i,N) cin>>A[i];

    vector<P> ans(M);
    Random_int raN(0,N-1);
    Random_int raM(0,M-1);
    repr(e,ans){
        e.first=raN.nextInt();
        e.second=raN.nextInt();
    }

    int score=computeScore(ans);
    while(TIMER.getTime()<=TIME_LIMIT) rep(nnn,100){
        int b=raN.nextInt()&1;
        int i=raM.nextInt();
        int val=raN.nextInt();
        int tmp_val;
        if(b){
            tmp_val=ans[i].second;
            ans[i].second=val;
        }else{
            tmp_val=ans[i].first;
            ans[i].first=val;
        }
        int tmp_socre=computeScore(ans);
        if(!adopt(tmp_socre-score)){
            if(b){
                ans[i].second=tmp_val;
            }else{
                ans[i].first=tmp_val;
            }
        }else{
            score=tmp_socre;
        }
    }

    repr(e,ans) cout<<e.first<<' '<<e.second<<endl;
    if(LOCALTEST) cout<<score<<endl;
    
    return 0;
}