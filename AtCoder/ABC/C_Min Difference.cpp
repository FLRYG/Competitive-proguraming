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

int N,M;
int A[200000];
int B[200000];

int main(){
    cin>>N>>M;
    rep(i,N) cin>>A[i];
    rep(i,M) cin>>B[i];

    sort(A,A+N);
    sort(B,B+M);

    int ans=INF;
    rep(i,N){
        int *p=lower_bound(B,B+M,A[i]);
        if(p!=B+M) ans=min(ans,abs(A[i]-*p));
        if(p!=B) ans=min(ans,abs(A[i]-*(p-1)));
    }

    cout<<ans<<endl;
    
    return 0;
}