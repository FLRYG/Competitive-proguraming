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

using T=P;
template<class T, T (*op)(T ,T), T (*e)()> struct segmentTree{
    int n;
    std::vector<T> v;
    segmentTree() : segmentTree(0){}
    segmentTree(int _n){
        n=1;
        while(n<_n) n*=2;
        v=std::vector<T>(2*n-1,e());
    }
    // segmentTree(vector<T> _v){
    //     n=1;
    //     while(n<_n) n*=2;
    //     data.resize(2*n-1);
    //     for(int i=0; i<_v.size(); i++) data[N-1+i]=_v[i];
    //     for(int n-2; i>=0; i--) data[i]=data[i*2+1]+data[i*2+2];
    // }
    void set(int k, T a){
        k+=n-1;
        v[k]=a;
        while(k>0){
            k=(k-1)/2;
            v[k]=op(v[k*2+1],v[k*2+2]);
        }
    }
    T get(int k){ return v[k+n-1]; }
    T query(int l, int r){ return query(l,r,0,0,n); }     // [l,r) 半開区間に注意
    T query(int l, int r, int k, int a, int b){
        if(b<=l || r<=a) return e();
        if(l<=a && b<=r) return v[k];
        T vl=query(l,r,k*2+1,a,(a+b)/2);
        T vr=query(l,r,k*2+2,(a+b)/2,b);
        return op(vl,vr);
    }
};
T op(T a, T b){
    if(a.first==b.first){
        if(a.second<b.second) return a;
        else return b;
    }else{
        if(a.first<b.first) return a;
        else return b;
    }
}
T e(){ return {INF,INF}; }

int N,K,D;
int A[200000];

int main() {
    cin>>N>>K>>D;
    rep(i,N) cin>>A[i];

    if(D*(K-1)+1>N){
        cout<<-1<<endl;
        return 0;
    }

    segmentTree<T,op,e> sg(N);
    rep(i,N) sg.set(i,{A[i],i});

    vector<int> ans(K);
    int r=N-D*(K-1);
    int l=0;
    rep(k,K){
        P p=sg.query(l,r);
        ans[k]=p.first;
        l=p.second+D;
        r+=D;
    }

    repr(e,ans) cout<<e<<' ';
    cout<<endl;
    
    return 0;
}