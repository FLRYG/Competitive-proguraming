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
typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int R,C;
int A[500][500];
int B[500][500];

int main() {
    cin>>R>>C;
    rep(i,R) rep(j,C-1) cin>>A[i][j];
    rep(i,R-1) rep(j,C) cin>>B[i][j];

    vector<vector<int>> cost(2*R,vector<int>(C,INF));
    priority_queue<IP,vector<IP>,greater<IP>> q;
    q.push({0,{0,0}});
    while(!q.empty()){
        IP ip=q.top();
        q.pop();
        int co=ip.first;
        int i=ip.second.first;
        int j=ip.second.second;
        if(cost[i][j]<=co) continue;
        cost[i][j]=co;
        if(i<R){
            if(j<C-1) q.push({co+A[i][j],{i,j+1}});
            if(j>0) q.push({co+A[i][j-1],{i,j-1}});
            if(i<R-1) q.push({co+B[i][j],{i+1,j}});
            q.push({co+1,{i+R,j}});
        }else{
            if(i>R) q.push({co+1,{i-1,j}});
            if(co<cost[i-R][j]) q.push({co,{i-R,j}});
        }

    }

    cout<<cost[R-1][C-1]<<endl;
    
    return 0;
}