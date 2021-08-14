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
double dp[201][101][101];
double tmp[201][101][101];

int main(){
    cin>>N>>D;

    int a=0, b=0, c=0;
    while(D%2==0) a++, D/=2;
    while(D%3==0) b++, D/=3;
    while(D%5==0) c++, D/=5;

    if(D>1){
        cout<<0<<endl;
        return 0;
    }

    dp[0][0][0]=1;
    rep(n,N){
        rep(i,2*n) rep(j,n) rep(k,n){
            tmp[i][j][k]+=dp[i][j][k]/6;
            tmp[i+1][j][k]+=dp[i][j][k]/6;
            tmp[i][j+1][k]+=dp[i][j][k]/6;
            tmp[i+2][j][k]+=dp[i][j][k]/6;
            tmp[i][j][k+1]+=dp[i][j][k]/6;
            tmp[i+1][j+1][k]+=dp[i][j][k]/6;
        }
        rep(i,2*n) rep(j,n) rep(k,n){
            dp[i][j][k]=tmp[i][j][k];
        }
    }

    double ans=0;
    for(;a<=200;a++) for(;b<=100;b++) for(;c<=100;c++){
        ans+=dp[a][b][c];
    }
    rep(i,N) ans/=6.0;

    cout<<ans<<endl;
    
    return 0;
}