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
typedef pair<ll,ll> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

ll Q;

int main(){
    cin>>Q;

    vector<ll> ans;
    priority_queue<ll,vector<ll>,greater<ll>> que;
    ll plus=0;
    while(Q--){
        ll t,X;
        cin>>t;
        if(t==1){
            cin>>X;
            que.push(X-plus);
        }else if(t==2){
            cin>>X;
            plus+=X;
        }else{
            ans.push_back(que.top()+plus);
            que.pop();
        }
    }

    repr(e,ans) cout<<e<<endl;
    
    return 0;
}