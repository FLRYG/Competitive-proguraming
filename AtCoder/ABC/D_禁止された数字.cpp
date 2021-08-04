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

ll f(string s){
    vector<vector<vector<ll>>> dp(s.size()+1,vector<vector<ll>>(2,vector<ll>(2,0)));
    dp[0][0][0]=1;
    rep(i,s.size()){
        int D=s[i]-'0';
        rep(j,2) rep(k,2) for(int d=0;d<=(j?9:D);d++){
            dp[i+1][j || (d<D)][k || d==4 || d==9]+=dp[i][j][k];
        }
    }
    return dp[s.size()][0][1]+dp[s.size()][1][1];
}

ll A,B;

int main(){
    cin>>A>>B;
    string a,b;
    a=to_string(A-1);
    b=to_string(B);

    ll ans=f(b)-f(a);
    cout<<ans<<endl;
    
    return 0;
}