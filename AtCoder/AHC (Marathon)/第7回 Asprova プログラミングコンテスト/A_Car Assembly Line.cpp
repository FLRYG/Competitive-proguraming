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

int M;              // 車の種類数 M
int S;              // 作業員の人数 S
int T;              // 車の流れる間隔 T[s]
int L;              // 一日の最大作業時間 L[s]
int t[41][81];      // 車種 i の車に対する作業ステーション j での必要作業時間 t[i][j]
int x[81];          // 作業ステーション j の大きさ [x[j-1],x[j]]
int n[41];          // 車種 i の需要 n[i]

void read(){
    cin>>M>>S>>T>>L;
    repn(i,M) repn(j,S) cin>>t[i][j];
    repn(j,S) cin>>x[j];
    repn(i,M) cin>>n[i];
}

vector<int> solve(){
    vector<int> ans;
    int K=0;
    repn(i,M) K+=n[i];
    repn(i,M) rep(j,n[i]) ans.push_back(i);

    return ans;
}

int main(){
    read();

    vector<int> ans=solve();

    cout<<ans.size()<<endl;
    repr(e,ans) cout<<e<<' ';
    cout<<endl;
    
    return 0;
}