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
int A[100000];
int B[100000];
int C[100000];

int main(){
    cin>>N;
    rep(i,N) cin>>A[i];
    rep(i,N) cin>>B[i];
    rep(i,N) cin>>C[i];

    sort(A,A+N);
    sort(B,B+N);
    sort(C,C+N);

    int ans=0, j=0, k=0;
    rep(i,N){
        while(j<N && A[i]>=B[j]) j++;
        if(j>=N) break;
        while(k<N && B[j]>=C[k]) k++;
        if(k>=N) break;
        ans++;
        j++, k++;
    }

    cout<<ans<<endl;

    return 0;
}