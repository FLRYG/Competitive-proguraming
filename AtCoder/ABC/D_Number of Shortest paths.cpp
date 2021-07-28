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
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

int N,M;

ll f(int v,vector<vector<int>> &G, vector<int> &time, vector<ll> &dp){
    if(v==0) return 1;
    if(dp[v]!=-1) return dp[v];
    ll res=0;
    repr(e,G[v]){
        if(time[e]==time[v]-1){
            res+=f(e,G,time,dp);
            res%=MOD;
        }
    }
    return dp[v]=res;
}

int main(){
    cin>>N>>M;
    vector<vector<int>> G(N);
    rep(i,M){
        int a,b;
        cin>>a>>b;
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    queue<P> q;
    q.push({0,0});
    vector<int> time(N,INF);
    while(!q.empty()){
        P p=q.front(); q.pop();
        int t=p.first;
        int v=p.second;
        if(t>=time[v]) continue;
        time[v]=t;
        repr(e,G[v]){
            if(time[e]==INF) q.push({t+1,e});
        }
    }

    vector<ll> dp(N,-1);
    ll ans=f(N-1,G,time,dp);

    cout<<ans<<endl;
    
    return 0;
}