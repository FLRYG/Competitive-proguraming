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

int N;
int A[1<<16+1];

int main() {
    cin>>N;
    rep(i,1<<N) cin>>A[i];

    int NN=1<<N;
    vector<int> ans(NN,N);
    vector<int> chk(NN,1);
    repn(n,N-1){
        int k=0, i, j;
        while(k<NN){
            while(k<NN && !chk[k]) k++;
            i=k++;
            while(k<NN && !chk[k]) k++;
            j=k++;
            if(i==NN) break;
            if(A[i]>A[j]){
                chk[j]=0;
                ans[j]=n;
            }else{
                chk[i]=0;
                ans[i]=n;
            }
        }
    }

    repr(e,ans) cout<<e<<endl;
    
    return 0;
}