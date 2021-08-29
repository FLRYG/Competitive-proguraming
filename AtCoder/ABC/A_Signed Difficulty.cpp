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

string S;

int main() {
    cin>>S;

    int y;
    string ans;
    if(S.size()==3){
        y=S[2]-'0';
        ans=S[0];
    }else{
        y=S[3]-'0';
        ans+=S[0];
        ans+=S[1];
    }
    
    if(y<=2){
        ans+='-'; 
    }else if(7<=y){
        ans+='+';
    }

    cout<<ans<<endl;
    
    return 0;
}