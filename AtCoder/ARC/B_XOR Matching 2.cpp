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

int N;
int a[2000];
int b[2000];

int main(){
    cin>>N;
    rep(i,N) cin>>a[i];
    rep(i,N) cin>>b[i];
    
    sort(b,b+N);

    vector<int> ans(0), bb(N);
    rep(i,N){
        int x=a[0]^b[i];
        rep(j,N) bb[j]=x^a[j];
        sort(bb.begin(),bb.end());
        bool flag=1;
        rep(j,N) flag&=b[j]==bb[j];
        if(flag) ans.push_back(x);
    }

    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());

    cout<<ans.size()<<endl;
    repr(e,ans) cout<<e<<endl;

    return 0;
}