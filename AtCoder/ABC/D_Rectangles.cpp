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

int N;
P xy[2000];

int main() {
    cin>>N;
    rep(i,N) cin>>xy[i].first>>xy[i].second;
    
    set<P> se;
    rep(i,N) se.insert(xy[i]);

    int ans=0;
    rep(i,N-1) for(int j=i+1;j<N;j++){
        if(xy[i].first==xy[j].first || xy[i].second==xy[j].second){
            continue;
        }
        if(se.find({xy[i].first,xy[j].second})!=se.end() &&
           se.find({xy[j].first,xy[i].second})!=se.end())
            ans++;
    }
    ans/=2;

    cout<<ans<<endl;

    return 0;
}