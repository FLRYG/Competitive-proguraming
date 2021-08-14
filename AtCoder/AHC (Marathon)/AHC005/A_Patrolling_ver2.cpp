#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <random>
#define rep(i,n) for(int i=0;i<n;i++)
#define repn(i,n) for(int i=1;i<=n;i++)
#define repr(e,x) for(auto& e:x)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
typedef pair<int,P> IP;
typedef pair<int,string> IS;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

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
const double TIME_LIMIT=2.9;
const double TEMPERATURE0=1e3;
const double TEMPERATURE1=6e2;
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

int const I[]={1,0,-1,0};
int const J[]={0,1,0,-1};
char const DIR[]={'D','R','U','L'};

int N, si, sj;
char c[71][71];

void read(){
    cin>>N>>si>>sj;
    si++, sj++;
    rep(i,N+2) c[0][i]='#';
    rep(i,N+2) c[N+1][i]='#';
    rep(i,N+2) c[i][0]='#';
    rep(i,N+2) c[i][N+1]='#';
    repn(i,N) repn(j,N) cin>>c[i][j];
}

int main(){
    TIMER.start();
    read();

    map<P,int> vertex;
    int V=1;
    vertex[{si,sj}]=0;
    repn(i,N) repn(j,N){
        int h=0, w=0;
        if(c[i-1][j]!='#' || c[i+1][j]!='#') h=1;
        if(c[i][j-1]!='#' || c[i][j+1]!='#') w=1;
        if(h && w && c[i][j]!='#') vertex[{i,j}]=V++;
    }

    if(LOCALTEST){
        cout<<"V: "<<V<<endl;
        repn(i,N){
            repn(j,N){
                if(i==si && j==sj) cout<<2;
                else if(vertex.find({i,j})!=vertex.end()) cout<<1;
                else cout<<0;
            }
            cout<<endl;
        }
    }

    vector<vector<IS>> G(V);
    repn(i,N) repn(j,N){
        if(vertex.find({i,j})!=vertex.end()){
            rep(k,4){
                int d=0, x=i, y=j;
                string s;
                do{
                    if(x==0 || x==N+1 || y==0 || y==N+1) goto exit;
                    x+=I[k];
                    y+=J[k];
                    if(c[x][y]=='#') goto exit;
                    d+=c[x][y]-'0';
                    s+=DIR[k];
                }while(vertex.find({x,y})==vertex.end());
                if(LOCALTEST) printf("%d,%d - %d,%d : d=%d, s=%s\n",i,j,x,y,d,s.c_str());
                G[vertex[{i,j}]][vertex[{x,y}]]={d,s};
                exit:;
            }
        }
    }

    if(LOCALTEST){
        rep(i,V) rep(j,V){
            printf("%d,%d : %d %s\n",i,j,G[i][j].first,G[i][j].second.c_str());
        }
        cout<<endl;
    }

    rep(i,V) G[i][i]={0,""};
    rep(k,V) rep(i,V) rep(j,V){
        if(G[i][k].first+G[k][j].first < G[i][j].first){
            G[i][j]={G[i][k].first+G[k][j].first, G[i][k].second+G[k][j].second};
        }
    }

    if(LOCALTEST){
        rep(i,V) rep(j,V){
            printf("%d,%d : %d %s\n",i,j,G[i][j].first,G[i][j].second.c_str());
        }
    }

    vector<int> route(V+1,0);
    rep(i,V) route[i]=i;

    // int travel_time=0;
    // rep(i,V) travel_time+=G[route[i]][route[i+1]].first;

    // double score;
    // score=round(1e4+1e7*(N/double(travel_time)));

    // Random_int rand(1,V-1);
    // while(TIMER.getTime()<=TIME_LIMIT){
    //     updateTemp(TIMER.getTime());

    //     int tmp_travel_time=travel_time;
    //     int x=rand.nextInt(), y=rand.nextInt();
    //     if(x==y) continue;
    //     if(abs(x-y)>1){
    //         tmp_travel_time-=G[route[x-1]][route[x]].first;
    //         tmp_travel_time-=G[route[x]][route[x+1]].first;
    //         tmp_travel_time-=G[route[y-1]][route[y]].first;
    //         tmp_travel_time-=G[route[y]][route[y+1]].first;
    //         swap(route[x],route[y]);
    //         tmp_travel_time+=G[route[x-1]][route[x]].first;
    //         tmp_travel_time+=G[route[x]][route[x+1]].first;
    //         tmp_travel_time+=G[route[y-1]][route[y]].first;
    //         tmp_travel_time+=G[route[y]][route[y+1]].first;
    //     }else if(x<y){
    //         tmp_travel_time-=G[route[x-1]][route[x]].first;
    //         tmp_travel_time-=G[route[x]][route[x+1]].first;
    //         tmp_travel_time-=G[route[y]][route[y+1]].first;
    //         swap(route[x],route[y]);
    //         tmp_travel_time+=G[route[x-1]][route[x]].first;
    //         tmp_travel_time+=G[route[x]][route[x+1]].first;
    //         tmp_travel_time+=G[route[y]][route[y+1]].first;
    //     }else{
    //         tmp_travel_time-=G[route[y-1]][route[y]].first;
    //         tmp_travel_time-=G[route[y]][route[y+1]].first;
    //         tmp_travel_time-=G[route[x]][route[x+1]].first;
    //         swap(route[x],route[y]);
    //         tmp_travel_time+=G[route[y-1]][route[y]].first;
    //         tmp_travel_time+=G[route[y]][route[y+1]].first;
    //         tmp_travel_time+=G[route[x]][route[x+1]].first;
    //     }

    //     double tmp_score=round(1e4+1e7*(N/double(tmp_travel_time)));
        
    //     if(!adopt(tmp_score-score)){
    //         swap(route[x],route[y]);
    //     }
    // }

    // if(LOCALTEST){
    //     rep(i,V) cout<<i<<' '<<route[i]<<endl;
    // }

    string ans;
    rep(i,V) ans+=G[route[i]][route[i+1]].second;
    cout<<ans<<endl;

    return 0;
}