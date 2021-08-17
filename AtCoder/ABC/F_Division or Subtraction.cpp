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

ll N;

int main() {
    cin>>N;

    set<ll> s;
    for(ll i=2;i<=1000000;i++){
        if(N%i==0){
            s.insert(i);
            s.insert(N/i);
        }
    }
    
    ll ans=0;
    repr(e,s){
        if(N/e%e==1) ans++;
    }

    N--;
    set<ll> s2;
    for(ll i=2;i<=1000000;i++){
        if(N%i==0){
            s2.insert(i);
            s2.insert(N/i);
        }
    }
    ans+=s2.size()-1;

    cout<<ans<<endl;

    return 0;
}