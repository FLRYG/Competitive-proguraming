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

int N;
int A[100];

int main() {
    cin>>N;
    rep(i,N) cin>>A[i];
    rep(i,N) A[i]--;

    vector<int> ans(N);
    rep(i,N){
        int x=A[i], cnt=1;
        while(x!=i){
            x=A[x];
            cnt++;
        }
        ans[i]=cnt;
    }

    repr(e,ans) cout<<e<<' '; cout<<endl;
    
    return 0;
}