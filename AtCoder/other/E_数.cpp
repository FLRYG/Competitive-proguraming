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

ll D;
string N;

ll dp[10001][2][100];

int main(){
    cin>>D>>N;

    int len=N.size();

    dp[0][0][0]=1;
    rep(i,len){
        int x=N[i]-'0';
        rep(j,2) for(int d=0;d<=(j?9:x);d++){
            rep(k,D){
                dp[i+1][j||(d<x)][(k+d)%D]+=dp[i][j][k];
                dp[i+1][j||(d<x)][(k+d)%D]%=MOD;
            }
        }
    }

    ll ans=(dp[len][0][0]+dp[len][1][0]-1+MOD)%MOD;

    cout<<ans<<endl;
    
    return 0;
}