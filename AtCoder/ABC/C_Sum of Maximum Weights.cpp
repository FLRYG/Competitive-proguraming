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

ll N;
ll S[200000];
ll T[200000];

int main(){
    cin>>N;
    rep(i,N) cin>>S[i];
    rep(i,N) cin>>T[i];

    int s, m=INF;
    rep(i,N){
        if(T[i]<m){
            m=T[i];
            s=i;
        }
    }

    rep(i,N){
        if(T[(s+i+1)%N]>T[(s+i)%N]+S[(s+i)%N]){
            T[(s+i+1)%N]=T[(s+i)%N]+S[(s+i)%N];
        }
    }

    rep(i,N) cout<<T[i]<<endl;
    
    return 0;
}