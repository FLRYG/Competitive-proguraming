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
// typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int N,K;
double w[1000];
double p[1000];

int main() {
    cin>>N>>K;
    rep(i,N) cin>>w[i]>>p[i];

    double l=0.0, r=100.0;
    while(r-l>1e-10){
        double X=(l+r)/2;
        vector<double> v(N);
        rep(i,N) v[i]=w[i]*(p[i]-X);
        sort(all(v));
        double sum=0;
        rep(i,K) sum+=v[N-1-i];
        if(sum>=0) l=X;
        else r=X;
    }

    printf("%.16lf\n",l);
    
    return 0;
}



// #include <iostream>
// #include <stdio.h>
// #include <algorithm>
// #include <cmath>
// #include <string>
// #include <vector>
// #include <list>
// #include <iomanip>
// #include <stack>
// #include <queue>
// #include <deque>
// #include <set>
// #include <map>
// #include <unordered_map>
// #include <bitset>
// #include <chrono>
// #include <random>
// #define rep(i,n) for(int i=0;i<n;i++)
// #define repn(i,n) for(int i=1;i<=n;i++)
// #define repr(e,x) for(auto& e:x)
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef pair<ll,ll> P;
// // typedef pair<int,P> IP;
// // typedef pair<P,P> PP;
// double const PI=3.141592653589793;
// int const INF=1001001001;
// ll const LINF=1001001001001001001;
// ll const MOD=1000000007;

// int N,K;
// ll w[1001];
// ll p[1001];

// int main(){
//     cin>>N>>K;   
//     repn(i,N) cin>>w[i]>>p[i];
//     vector<double> salt(N+1,0);
//     repn(i,N) salt[i]=w[i]*p[i]/100.0;

//     vector<vector<P>> dp(N+1,vector<P>(N+1));
//     repn(i,N){
//         for(int j=1;j<=i;j++){
//             dp[i][j]=dp[i-1][j];
//             double c1=(double)dp[i-1][j].second/dp[i-1][j].first;
//             double c2=(double)(dp[i-1][j-1].second+salt[i])/(dp[i-1][j-1].first+w[i]);
//             if(c1>c2 || c1==c2 && dp[i-1][j].first<=dp[i-1][j-1].first+w[i]){
//                 dp[i][j]=dp[i-1][j];
//             }else{
//                 dp[i][j]={dp[i-1][j-1].first+w[i],dp[i-1][j-1].second+salt[i]};
//             }
//         }
//     }

//     double ans=double(dp[N][K].second)/dp[N][K].first;
//     cout<<ans<<endl;
    
//     return 0;
// }