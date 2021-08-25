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

int N,M;
int S[200000];
int T[200000];

int main() {
    cin>>N>>M;
    rep(i,N) cin>>S[i];
    rep(i,M) cin>>T[i];
    
    int s=0, t=0;
    rep(i,N) s|=1<<S[i];
    rep(i,M) t|=1<<T[i];

    rep(i,2) if((s>>i&1)==0 && (t>>i&1)==1){
        cout<<-1<<endl;
        return 0;
    }

    int ans=0, d=0, e=0;
    if(t==1){
        while(S[d]!=0) d++; 
        while(S[e]!=0) e=(e-1+N)%N;
        ans=M+min(d,N-e);
    }else if(t==2){
        while(S[d]!=1) d++; 
        while(S[e]!=1) e=(e-1+N)%N;
        ans=M+min(d,N-e);
    }else{
        while(S[d]==S[d+1]) d++;
        while(S[e]==S[(e-1+N)%N]) e=(e-1+N)%N;
        if(d<=(N-e)%N){
            ans+=M+d;
            if(S[d]!=T[0]) ans++;
            rep(i,M-1) if(T[i]!=T[i+1]) ans++;
        }else{
            ans+=M+(N-e)%N;
            if(S[e]!=T[0]) ans++;
            rep(i,M-1) if(T[i]!=T[i+1]) ans++;
        }
    }

    cout<<ans<<endl;

    return 0;
}