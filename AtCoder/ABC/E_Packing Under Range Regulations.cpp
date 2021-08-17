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
typedef pair<int, int> P;
// typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

int T;

int main() {
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        vector<P> LR(N);
        rep(i, N) cin >> LR[i].first >> LR[i].second;

        sort(LR.begin(),LR.end());

        priority_queue<int, vector<int>, greater<int>> q;
        int pos=LR[0].first, i=0;
        while(pos<INF){
            while(i<N && pos==LR[i].first) q.push(LR[i++].second);
            int x=q.top();
            q.pop();
            if(q.empty()){
                if(i<N) pos=LR[i].first;
                else break;
            }
            else{
                if(q.top()<=pos){
                    cout<<"No"<<endl;
                    goto exit;
                }
                pos++;
            }
        }
        cout<<"Yes"<<endl;
        exit:;
    }

    return 0;
}

// #include <iostream>
// #include <stdio.h>
// #include <algorithm>
// #include <cmath>
// #include <string>
// #include <vector>
// #include <list>
// #include <iomanip>
// #include <stack>
// #include <queue>
// #include <deque>
// #include <set>
// #include <map>
// #include <unordered_map>
// #include <bitset>
// #include <chrono>
// #include <random>
// #define rep(i,n) for(int i=0;i<n;i++)
// #define repn(i,n) for(int i=1;i<=n;i++)
// #define repr(e,x) for(auto& e:x)
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef pair<int,int> P;
// // typedef pair<int,P> IP;
// // typedef pair<P,P> PP;
// double const PI=3.141592653589793;
// int const INF=1001001001;
// ll const LINF=1001001001001001001;
// ll const MOD=1000000007;

// int T,N;

// int main(){
//     cin>>T;

//     while(T--){
//         int N;
//         cin>>N;
//         vector<P> LR(N);
//         rep(i,N) cin>>LR[i].first>>LR[i].second;
//         sort(LR.begin(),LR.end(),[&](P i, P j){
//             if(i.second!=j.second) return i.second<j.second;
//             return i.first<j.first;
//         });
//         sort(LR.begin(),LR.end());

//         int l=1;
//         rep(i,N){
//             if(l<=LR[i].second){
//                 l=max(l,LR[i].first)+1;
//             }else{
//                 cout<<"No"<<endl;
//                 goto exit;
//             }
//         }
//         cout<<"Yes"<<endl;
//         exit:;
//     }

//     return 0;
// }