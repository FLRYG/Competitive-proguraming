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

int L,Q;

int main() {
    cin>>L>>Q;

    set<int> se;
    se.insert(0);
    se.insert(L);
    vector<int> ans;
    while(Q--){
        int c,x;
        cin>>c>>x;
        if(c==1){
            se.insert(x);
        }else{
            auto i=se.lower_bound(x);
            int x=*i;
            i--;
            int y=*i;
            ans.push_back(x-y);
        }
    }

    repr(e,ans) cout<<e<<endl;
    
    return 0;
}