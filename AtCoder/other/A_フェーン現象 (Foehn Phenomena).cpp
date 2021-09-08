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

template <class T, T (*op)(T, T), T (*e)()>
struct segmentTree {
    int n;
    std::vector<T> v;
    segmentTree() : segmentTree(0) {}
    segmentTree(int _n) {
        n = 1;
        while (n < _n) n *= 2;
        v = std::vector<T>(2 * n - 1, e());
    }
    // segmentTree(vector<T> _v){
    //     n=1;
    //     while(n<_n) n*=2;
    //     data.resize(2*n-1);
    //     for(int i=0; i<_v.size(); i++) data[N-1+i]=_v[i];
    //     for(int n-2; i>=0; i--) data[i]=data[i*2+1]+data[i*2+2];
    // }
    void set(int k, T a) {
        k += n - 1;
        v[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            v[k] = op(v[k * 2 + 1], v[k * 2 + 2]);
        }
    }
    T get(int k) { return v[k + n - 1]; }
    T query(int l, int r) {
        return query(l, r, 0, 0, n);
    }  // [l,r) 半開区間に注意
    T query(int l, int r, int k, int a, int b) {
        if (b <= l || r <= a) return e();
        if (l <= a && b <= r) return v[k];
        T vl = query(l, r, k * 2 + 1, a, (a + b) / 2);
        T vr = query(l, r, k * 2 + 2, (a + b) / 2, b);
        return op(vl, vr);
    }
};
ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

ll N, Q, S, T;
ll A[200001];

int main() {
    cin >> N >> Q >> S >> T;
    rep(i, N+1) cin >> A[i];

    ll temp=0;
    rep(i,N){
        if(A[i]<A[i+1]) temp+=-S*(A[i+1]-A[i]);
        else temp+=T*(A[i]-A[i+1]);
        cout<<temp<<endl;
    }

    segmentTree<ll,op,e> sg(N+2);
    vector<ll> ans;
    while (Q--) {
        int L, R, X;
        cin>>L>>R>>X;
        ll x, y;
        if(L>0){
            x=sg.query(0,L)+A[L-1];
            y=sg.query(0,L+1)+A[L];
            if(x<y) temp-=-S*(y-x);
            else temp-=T*(y-x);
        }
        if(R<N){
            x=sg.query(0,R+1)+A[R];
            y=sg.query(0,R+2)+A[R+1];
            if(x<y) temp-=-S*(y-x);
            else temp-=T*(y-x);
        }
        sg.set(L,sg.get(L)+X);
        sg.set(R+1,sg.get(R+1)-X);
        if(L>0){
            x=sg.query(0,L)+A[L-1];
            y=sg.query(0,L+1)+A[L];
            if(x<y) temp+=-S*(y-x);
            else temp+=T*(y-x);
        }
        if(R<N){
            x=sg.query(0,R+1)+A[R];
            y=sg.query(0,R+2)+A[R+1];
            if(x<y) temp+=-S*(y-x);
            else temp+=T*(y-x);
        }
        rep(i,N+1) cout<<sg.query(0,i+1)+A[i]<<' '; cout<<endl;
        ans.push_back(temp);
    }

    repr(e,ans) cout<<e<<endl;

    return 0;
}