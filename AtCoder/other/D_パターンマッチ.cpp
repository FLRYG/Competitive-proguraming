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

string S;

int main() {
    cin>>S;
    int N;
    N=S.size();

    set<string> se;
    se.insert(".");
    rep(i,N){
        string t=S.substr(i,1);
        se.insert(t);
    }
    rep(i,N-1){
        rep(j,4){
            string t=S.substr(i,2);
            rep(k,2) if(j>>k&1) t[k]='.';
            se.insert(t);
        }
    }
    rep(i,N-2){
        rep(j,8){
            string t=S.substr(i,3);
            rep(k,3) if(j>>k&1) t[k]='.';
            se.insert(t);
        }
    }

    cout<<se.size()<<endl;
    
    return 0;
}