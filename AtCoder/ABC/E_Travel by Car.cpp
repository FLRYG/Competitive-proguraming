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

int N,M,L,Q;

int main() {
    cin>>N>>M>>L;

    vector<vector<ll>> G(N,vector<ll>(N,LINF));
    rep(i,M){
        int a,b,c;
        cin>>a>>b>>c;
        a--, b--;
        G[a][b]=c;
        G[b][a]=c;
    }
    rep(i,N) G[i][i]=0;
    rep(k,N) rep(i,N) rep(j,N){
        G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
    }

    vector<vector<int>> cost(N,vector<int>(N,INF));
    rep(i,N) cost[i][i]=0;
    rep(i,N) rep(j,N){
        if(G[i][j]<=L) cost[i][j]=1;
    }
    rep(k,N) rep(i,N) rep(j,N){
        cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
    }

    cin>>Q;
    while(Q--){
        int s,t;
        cin>>s>>t;
        s--, t--;
        if(cost[s][t]==INF) cout<<-1<<endl;
        else cout<<cost[s][t]-1<<endl;
    }
    
    return 0;
}