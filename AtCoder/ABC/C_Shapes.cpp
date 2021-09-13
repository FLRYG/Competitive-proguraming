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

int N;
string S[200], T[200];

int main() {
    cin >> N;
    rep(i, N) cin >> S[i];
    rep(i, N) cin >> T[i];

    int su = INF, sl = INF, sd = -1, sr = -1, sh, sw;
    rep(i, N) rep(j, N) {
        if (S[i][j] == '#') {
            su = min(su, i);
            sl = min(sl, j);
            sd = max(sd, i);
            sr = max(sr, j);
        }
    }
    sh=sd-su+1;
    sw=sr-sl+1;

    int tu = INF, tl = INF, td = -1, tr = -1, th, tw;
    rep(i, N) rep(j, N) {
        if (T[i][j] == '#') {
            tu = min(tu, i);
            tl = min(tl, j);
            td = max(td, i);
            tr = max(tr, j);
        }
    }
    th=td-tu+1;
    tw=tr-tl+1;

    // rep(i,sh) {
    //     rep(j,sw){
    //         cout<<S[su+i][sl+j]<<' ';
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    // rep(i,th) {
    //     rep(j,tw){
    //         cout<<T[tu+i][tl+j]<<' ';
    //     }
    //     cout<<endl;
    // }

    if(sh==th && sw==tw){
        bool fl=true;
        rep(i,sh) rep(j,sw){
            if(S[su+i][sl+j]!=T[tu+i][tl+j]) fl=false;
        }
        if(fl){
            cout<<"Yes"<<endl;
            return 0;
        }
        fl=true;
        rep(i,sh) rep(j,sw){
            if(S[su+i][sl+j]!=T[td-i][tr-j]) fl=false;
        }
        if(fl){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    if(sh==tw && sw==th){
        bool fl=true;
        rep(i,sh) rep(j,sw){
            if(S[su+i][sl+j]!=T[td-j][tl+i]) fl=false;
        }
        if(fl){
            cout<<"Yes"<<endl;
            return 0;
        }
        fl=true;
        rep(i,sh) rep(j,sw){
            if(S[su+i][sl+j]!=T[tu+j][tr-i]) fl=false;
        }
        if(fl){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    cout<<"No"<<endl;

    return 0;
}