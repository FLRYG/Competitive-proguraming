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

ll mpow(ll x,ll n){
    if(n==0) return 1;
    else if(n&1) return x*mpow(x,n-1);
    return mpow(x*x,n/2);
}

int K;
int R[1025];

int main(){
    cin>>K;
    int N=mpow(2,K);
    rep(i,N) cin>>R[i];

    vector<vector<double>> dp(K+1,vector<double>(N,0));
    rep(i,N) dp[0][i]=1;
    repn(i,K){
        int n=mpow(2,i);
        rep(j,N){
            int l=j/n*n, r=(j/n+1)*n;
            if(j<l+n/2) l+=n/2;
            else r-=n/2;
            while(l<r){
                dp[i][j]+=dp[i-1][l]/(1+pow(10,(R[l]-R[j])/400.0));
                l++;
            }
            dp[i][j]*=dp[i-1][j];
        }
    }

    cout<<setprecision(16);
    rep(i,N){
        printf("%.16lf\n",dp[K][i]);
    }
    
    return 0;
}