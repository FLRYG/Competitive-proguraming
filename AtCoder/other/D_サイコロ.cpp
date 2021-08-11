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

ll N,D;
ll dp[201][101][101];
ll tmp[201][101][101];

int main(){
    cin>>N>>D;

    dp[0][0][0]=1;
    rep(n,N){
        rep(i,100) rep(j,100) rep(k,100){
            tmp[i][j][k]+=dp[i][j][k];
            tmp[i+1][j][k]+=dp[i][j][k];
            tmp[i][j+1][k]+=dp[i][j][k];
            tmp[i+2][j][k]+=dp[i][j][k];
            tmp[i][j][k+1]+=dp[i][j][k];
            tmp[i+1][j+1][k]+=dp[i][j][k];
        }
        rep(i,100) rep(j,100) rep(k,100){
            dp[i][j][k]=tmp[i][j][k];
        }
    }

    
    
    return 0;
}