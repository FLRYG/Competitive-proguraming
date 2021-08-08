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
// typedef pair<int,int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

void f(int v, int p, vector<vector<int>> &G){
    cout<<v+1<<' ';
    repr(e,G[v]) if(e!=p){
        f(e,v,G);
        cout<<v+1<<' ';
    }
}

int N;

int main(){
    cin>>N;
    vector<vector<int>> G(N);
    rep(i,N-1){
        int a,b;
        cin>>a>>b;
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    rep(i,N) sort(G[i].begin(),G[i].end());

    f(0,-1,G);
    cout<<endl;
    
    return 0;
}