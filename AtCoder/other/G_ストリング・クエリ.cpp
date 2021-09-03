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

    vector<P> v;
    v.reserve(Q);
    int k=0;
    while(Q--){
        int t;
        cin>>t;
        if(t==1){
            char C;
            int X;
            cin>>C>>X;
            v.push_back({C-'a',X});
        }else{
            int D;
            cin>>D;
            vector<ll> cnt(26);
            while(k<v.size() && D>0){
                if(D>=v[k].second){
                    cnt[v[k].first]+=v[k].second;
                    D-=v[k].second;
                    k++;
                }else{
                    cnt[v[k].first]+=D;
                    v[k].second-=D;
                    D=0;
                }
            }
            ll sum=0;
            rep(i,26) sum+=cnt[i]*cnt[i];
            cout<<sum<<endl;
        }
    }
    
    return 0;
}