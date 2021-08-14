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

int N,Q;
int y[52];
string name[52];

int main(){
    cin>>N>>Q;
    repn(i,N) cin>>y[i]>>name[i];
    name[0]="kogakubu10gokan";
    y[N+1]=INF;

    rep(i,N+1){
        if(y[i]<=Q && Q<y[i+1]){
            cout<<name[i]<<endl;
            break;
        }
    }

    return 0;
}