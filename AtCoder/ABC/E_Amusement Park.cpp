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

ll N,K;
ll A[100001];

int main() {
    cin>>N>>K;
    rep(i,N) cin>>A[i];

    A[N]=0;
    sort(A,A+N+1,greater<int>());

    ll ans=0;
    rep(i,N){
        ll dif=A[i]-A[i+1];
        if(dif*(i+1)<=K){
            K-=dif*(i+1);
            ans+=(dif*A[i+1]+dif*(dif+1)/2)*(i+1);
        }else{
            ll cnt=K/(i+1);
            ll mod=K%(i+1);
            ans+=(cnt*(A[i]-cnt)+cnt*(cnt+1)/2)*(i+1);
            ans+=(A[i]-cnt)*mod;
            break;
        }
    }

    cout<<ans<<endl;

    return 0;
}