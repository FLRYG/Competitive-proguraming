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

int N,M;

int main() {
    cin>>N>>M;
    vector<vector<int>> id(N,vector<int>(N,INF));
    vector<vector<int>> G(N);
    rep(i,M){
        int s,t;
        cin>>s>>t;
        s--, t--;
        id[s][t]=i;
        G[s].push_back(t);
    }

    rep(i,M){
        queue<P> q;
        vector<int> cost(N,INF);
        q.push({0,0});
        while(!q.empty()){
            P p=q.front();
            q.pop();
            int c=p.first;
            int v=p.second;
            if(cost[v]<=c) continue;
            cost[v]=c;
            repr(e,G[v]){
                if(id[v][e]!=i && c+1<cost[e]) q.push({c+1,e});
            }
        }
        int ans=cost[N-1];
        if(ans==INF) ans=-1;
        cout<<ans<<endl;
    }
    
    return 0;
}