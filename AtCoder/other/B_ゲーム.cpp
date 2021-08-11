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

int A,B;
int a[1001];
int b[1001];

int main(){
    cin>>A>>B;
    repn(i,A) cin>>a[i];
    repn(i,B) cin>>b[i];

    vector<vector<int>> dp(A+1,vector<int>(B+1));
    repn(i,A) dp[i][0]=a[A-i+1]-dp[i-1][0];
    repn(j,B) dp[0][j]=b[B-j+1]-dp[0][j-1];
    repn(i,A) repn(j,B){
        dp[i][j]=max(a[A-i+1]-dp[i-1][j],b[B-j+1]-dp[i][j-1]);
    }

    int ans=dp[A][B];
    repn(i,A) ans+=a[i];
    repn(i,B) ans+=b[i];
    ans/=2;

    cout<<ans<<endl;
    
    return 0;
}