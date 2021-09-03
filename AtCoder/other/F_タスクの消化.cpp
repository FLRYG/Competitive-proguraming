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
typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int N;
P AB[200000];

int main() {
    cin>>N;
    rep(i,N) cin>>AB[i].first>>AB[i].second;

    sort(AB,AB+N);

    int k=0;
    vector<int> ans(N+1);
    priority_queue<int> q;
    repn(i,N){
        while(k<N && AB[k].first<=i) q.push(AB[k++].second);
        ans[i]=ans[i-1];
        if(!q.empty()){
            ans[i]+=q.top();
            q.pop();
        }
    }

    repn(i,N) cout<<ans[i]<<endl;
    
    return 0;
}