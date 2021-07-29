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

ll A[3];

int main(){
    rep(i,3) cin>>A[i];

    ll b=A[1]-A[0];
    ll c=A[2]-A[1];
    ll ans;
    if(b<=c){
        ans=(c-b+1)/2;
        if((b&1)!=(c&1)) ans++;
    }else{
        ans=b-c;
    }

    cout<<ans<<endl;
    
    return 0;
}