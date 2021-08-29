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

int N,M;

int main() {
    cin>>N>>M;
    vector<int> k(M);
    vector<vector<int>> a(M);
    rep(i,M){
        cin>>k[i];
        a[i].resize(k[i]);
        rep(j,k[i]){
            cin>>a[i][j];
            a[i][j]--;
        }
    }

    vector<vector<int>> pos(N);
    rep(i,M) rep(j,k[i]){
        pos[a[i][j]].push_back(i);
    }

    vector<int> id(M,0);
    vector<set<int>> cnt(3);
    vector<int> cnt2(N,0);
    rep(i,M) cnt2[a[i][0]]++;
    rep(i,N){
        cnt[cnt2[i]].insert(i);
    }
    while(!cnt[2].empty()){
        int val=*cnt[2].begin();
        cnt[2].erase(val);
        rep(j,2){
            int i=pos[val][j];
            id[i]++;
            if(id[i]<k[i]){
                int v=a[i][id[i]];
                if(cnt2[v]==0){
                    cnt2[v]++;
                    cnt[1].insert(v);
                }else if(cnt2[v]==1){
                    cnt2[v]++;
                    cnt[1].erase(v);
                    cnt[2].insert(v);
                }
            }
        }
    }

    rep(i,M) if(id[i]<k[i]){
        cout<<"No"<<endl;
        return 0;
    }

    cout<<"Yes"<<endl;
    
    return 0;
}