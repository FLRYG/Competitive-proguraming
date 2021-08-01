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

string X;

int main(){
    cin>>X;

    string ans="Strong";

    bool flag=1;
    rep(i,3) flag&=X[i]==X[i+1];
    if(flag) ans="Weak";

    flag=1;
    rep(i,3){
        int a=X[i]-'0';
        int b=X[i+1]-'0';
        if(a<=8 && a+1==b) flag&=1;
        else if(a==9 && b==0) flag&=1;
        else flag=0;
    }
    if(flag) ans="Weak";

    cout<<ans<<endl;
    
    return 0;
}