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
typedef pair<ll, ll> P;
typedef pair<ll,P> IP;
// typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

using T=ll;
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
T op(T a, T b){ return a+b; }
T e(){ return 0; }

int N,Q;
ll X[50000];
ll Y[50000];
ll D[50000];
ll C[50000];
ll A[100000];
ll B[100000];

int main() {
    cin>>N>>Q;
    rep(i,N) cin>>X[i]>>Y[i]>>D[i]>>C[i];
    rep(i,Q) cin>>A[i]>>B[i];

    map<ll,ll> yinv;
    rep(i,N){
        yinv[Y[i]];
        yinv[Y[i]+D[i]+1];
    }
    rep(i,Q) yinv[B[i]];
    int k=0;
    repr(e,yinv) e.second=k++;

    vector<IP> x;
    x.reserve(N+Q);
    rep(i,N){
        x.push_back({X[i],{0,i}});
    }
    rep(i,Q) x.push_back({A[i],{1,i}});
    sort(all(x));

    // cout<<endl;
    // repr(e,x) cout<<e.first<<' '<<e.second.first<<' '<<e.second.second<<endl;
    // cout<<endl;

    vector<ll> ans(Q);
    priority_queue<P,vector<P>,greater<P>> que;
    segmentTree<T,op,e> sg(yinv.size());
    rep(i,N+Q){
        ll p=x[i].first;
        ll id=x[i].second.second;
        // cout<<p<<endl;
        while(!que.empty() && que.top().first<p){
            ll j=que.top().second;
            sg.set(yinv[Y[j]],sg.get(yinv[Y[j]])-C[j]);
            sg.set(yinv[Y[j]+D[j]+1],sg.get(yinv[Y[j]+D[j]+1])+C[j]);
            // printf("delete: (%lld,%lld) %lld\n",Y[j],Y[j]+D[j],C[j]);
            que.pop();
        }
        if(x[i].second.first==0){
            sg.set(yinv[Y[id]],sg.get(yinv[Y[id]])+C[id]);
            sg.set(yinv[Y[id]+D[id]+1],sg.get(yinv[Y[id]+D[id]+1])-C[id]);
            // printf("add: (%lld,%lld) %lld\n",Y[id],Y[id]+D[id],C[id]);
            que.push({p+D[id],id});
        }else{
            // printf("ans: (%lld,%lld) %lld\n",A[id],B[id],sg.query(0,yinv[B[id]]+1));
            ans[id]=sg.query(0,yinv[B[id]]+1);
        }
    }
    
    repr(e,ans) cout<<e<<endl;
    
    return 0;
}