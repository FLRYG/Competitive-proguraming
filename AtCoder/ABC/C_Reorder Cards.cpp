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
typedef pair<int,int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

int H,W,N;
P A[100001];
P B[100001];

int main(){
    cin>>H>>W>>N;
    repn(i,N) cin>>A[i].first>>B[i].first;
    repn(i,N) A[i].second=i, B[i].second=i;

    sort(A+1,A+N+1);
    sort(B+1,B+N+1);

    int x=0, y=0;
    vector<int> C(N+1),D(N+1);
    repn(i,N){
        if(A[i-1].first==A[i].first){
            C[A[i].second]=x;
        }else{
            C[A[i].second]=++x;
        }
    }
    repn(i,N){
        if(B[i-1].first==B[i].first){
            D[B[i].second]=y;
        }else{
            D[B[i].second]=++y;
        }
    }

    repn(i,N) cout<<C[i]<<' '<<D[i]<<endl;
    
    return 0;
}