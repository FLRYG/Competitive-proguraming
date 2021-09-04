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

int Q;

int main() {
    cin>>Q;

    priority_queue<int,vector<int>,greater<int>> q;
    queue<int> r;
    vector<int> ans;
    while(Q--){
        int t;
        cin>>t;
        if(t==1){
            int x;
            cin>>x;
            r.push(x);
        }else if(t==2){
            if(q.empty()){
                ans.push_back(r.front());
                r.pop();
            }else{
                ans.push_back(q.top());
                q.pop();
            }
        }else{
            while(!r.empty()){
                q.push(r.front());
                r.pop();
            }
        }
    }

    repr(e,ans) cout<<e<<endl;
    
    return 0;
}