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

ll N, K;
ll A[200000];

int main() {
    cin >> N >> K;
    rep(i, N) cin >> A[i];

    sort(A, A + N);

    ll pos = 0, neg = 0, zer = 0;
    rep(i, N) {
        if (A[i] < 0)
            neg++;
        else if (A[i] > 0)
            pos++;
        else
            zer++;
    }

    ll ans = 1;
    if (K > pos + neg) {
        // cout<<"aaa"<<endl;
        ans = 0;
    } else if (K%2==1 && neg==N) {
        // cout<<"ccc"<<endl;
        rep(i, N) {
            if (A[i] < 0) A[i] *= -1;
        }
        sort(A, A + N);
        rep(i, K) ans = ans * A[i] % MOD;
        ans = (MOD - ans) % MOD;
    } else {
        // cout<<"bbb"<<endl;
        int l = 0, r = N - 1;
        while (K > 1) {
            if (A[l] * A[l + 1] >= A[r - 1] * A[r]) {
                ans = ans * A[l] % MOD * A[l + 1] % MOD;
                l += 2;
            } else {
                ans = ans * A[r - 1] % MOD * A[r] % MOD;
                r -= 2;
            }
            K -= 2;
        }
        if (K == 1) ans = ans * A[r] % MOD;
        if (ans < 0) ans += MOD;
    }

    cout << ans << endl;

    return 0;
}


// #include <stdio.h>

// #include <algorithm>
// #include <bitset>
// #include <chrono>
// #include <cmath>
// #include <deque>
// #include <functional>
// #include <iomanip>
// #include <iostream>
// #include <list>
// #include <map>
// #include <queue>
// #include <random>
// #include <set>
// #include <stack>
// #include <string>
// #include <unordered_map>
// #include <vector>
// #define rep(i, n) for (int i = 0; i < n; i++)
// #define repn(i, n) for (int i = 1; i <= n; i++)
// #define repr(e, x) for (auto& e : x)
// #define all(x) (x).begin(), (x).end()
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// // typedef pair<int, int> P;
// // typedef pair<int,P> IP;
// // typedef pair<P,P> PP;
// double const PI = 3.141592653589793;
// int const INF = 1001001001;
// ll const LINF = 1001001001001001001;
// ll const MOD = 1000000007;

// ll N, K;
// ll A[200000];

// int main() {
//     cin >> N >> K;
//     rep(i, N) cin >> A[i];

//     sort(A, A + N);

//     ll pos = 0, neg = 0, zer = 0;
//     rep(i, N) {
//         if (A[i] < 0)
//             neg++;
//         else if (A[i] > 0)
//             pos++;
//         else
//             zer++;
//     }

//     ll ans = 1;
//     if (K > pos + neg) {
//         // cout<<"aaa"<<endl;
//         ans = 0;
//     } else if ((pos == 0 && K % 2 == 0) || (pos == 1 && K % 2 == 1) ||
//                (pos >= 2 && K <= neg / 2 * 2 + pos)) {
//         // cout<<"bbb"<<endl;
//         int l = 0, r = N - 1;
//         while (K > 1) {
//             if (A[l] * A[l + 1] >= A[r - 1] * A[r]) {
//                 ans = ans * A[l] % MOD * A[l + 1] % MOD;
//                 l += 2;
//             } else {
//                 ans = ans * A[r - 1] % MOD * A[r] % MOD;
//                 r -= 2;
//             }
//             K -= 2;
//         }
//         if (K == 1) ans = ans * A[r] % MOD;
//         if (ans < 0) ans += MOD;
//     } else {
//         // cout<<"ccc"<<endl;
//         rep(i, N) {
//             if (A[i] < 0) A[i] *= -1;
//         }
//         sort(A, A + N);
//         rep(i, K) ans = ans * A[i] % MOD;
//         ans = (MOD - ans) % MOD;
//     }

//     cout << ans << endl;

//     return 0;
// }

// // #include <iostream>
// // #include <stdio.h>
// // #include <algorithm>
// // #include <cmath>
// // #include <string>
// // #include <vector>
// // #include <iomanip>
// // #include <queue>
// // #include <deque>
// // #include <map>
// // #include <unordered_map>
// // #define rep(i,n) for(int i=0;i<n;i++)
// // #define repn(i,n) for(int i=1;i<=n;i++)
// // #define repr(e,x) for(auto& e:x)
// // using namespace std;
// // typedef long long ll;
// // typedef long double ld;
// // typedef pair<ll,ll> P;
// // typedef pair<ll,pair<ll,ll>> PP;

// // const ll MOD=1'000'000'007;

// // ll N,K;
// // ll A[200001];
// // ll zero;
// // PP dp[200001];

// // int main(){
// //     cin>>N>>K;
// //     repn(i,N){
// //         cin>>A[i];
// //         if(A[i]==0) zero++;
// //     }
// //     if(K>N-zero){
// //         cout<<0<<endl;
// //         return 0;
// //     }
// //     sort(A+1,A+N+1);
// //     repn(i,N)cout<<A[i]<<' ';cout<<endl;

// //     dp[0]=PP(1,P(1,N));
// //     dp[1]=PP(A[N],P(1,N-1));
// //     for(int i=2;i<=N;i++){
// //         ll x_2=dp[i-2].first;
// //         ll x_1=dp[i-1].first;
// //         ll v_2=x_2*A[dp[i-2].second.first]*A[dp[i-2].second.first+1];
// //         ll v_1=x_1*A[dp[i-1].second.second];
// //         if(v_2>=v_1){
// //             dp[i]=PP(v_2,P(dp[i-2].second.first+2,dp[i-2].second.second));
// //         }else{
// //             dp[i]=PP(v_1,P(dp[i-1].second.first,dp[i-1].second.second-1));
// //         }
// //         dp[i].first%=MOD;
// //     }

// //     rep(i,K) cout<<dp[i].first<<endl;
// //     cout<<dp[K].first<<endl;
// // }