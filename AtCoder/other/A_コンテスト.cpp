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

int N;
int p[100];

int main(){
    cin>>N;
    rep(i,N) cin>>p[i];

    vector<vector<int>> dp(N+1,vector<int>(100*N+1,0));
    dp[0][0]=1;
    rep(i,N) rep(j,i*100+1){
        dp[i+1][j]|=dp[i][j];
        dp[i+1][j+p[i]]|=dp[i][j];
    }

    int ans=0;
    rep(i,N*100+1) ans+=dp[N][i];

    cout<<ans<<endl;
    
    return 0;
}