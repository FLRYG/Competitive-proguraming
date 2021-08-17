#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <deque>
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
// typedef pair<ll, ll> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int N;
int p[20001];

int main() {
    cin>>N;
    repn(i,N) cin>>p[i];

    vector<int> a(N+2), b(N+2);
    repn(i,N){
        a[p[i+1]]+=1;
        b[p[i-1]]+=1;
    }
    repn(i,N){
        a[i]+=a[i-1];
        b[N-i+1]+=b[N-i+2];
    }
    repn(i,N){
        a[i]+=i;
        b[i]+=N-i+1;
    }

    repn(i,N) cout<<a[i]<<' '; cout<<endl;
    repn(i,N) cout<<b[i]<<' '; cout<<endl;
    
    return 0;
}