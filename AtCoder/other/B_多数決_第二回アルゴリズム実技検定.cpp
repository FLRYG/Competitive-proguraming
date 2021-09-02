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

string s;

int main() {
    cin>>s;

    vector<int> cnt(3);
    rep(i,s.size()) cnt[s[i]-'a']++;

    char ans;
    if(cnt[0]>cnt[1] && cnt[0]>cnt[2]) ans='a';
    if(cnt[1]>cnt[0] && cnt[1]>cnt[2]) ans='b';
    if(cnt[2]>cnt[0] && cnt[2]>cnt[1]) ans='c';

    cout<<ans<<endl;
    
    return 0;
}