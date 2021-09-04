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
typedef pair<P,P> PP;
double const PI = 3.141592653589793;
int const INF = 1001001001;
ll const LINF = 1001001001001001001;
ll const MOD = 1000000007;

struct UnionFind{
    int n;
    vector<int> par;                       //親
    vector<int> rank;                      //木の深さ
    vector<int> scale;                     //木のサイズ
    int quantity;                          //木の個数
    UnionFind(int _n): n(_n){
        par.resize(n);
        rank.resize(n);
        scale.resize(n);
        quantity=n;
        for(int i=0;i<n;i++){
            par[i]=i;
            rank[i]=0;
            scale[i]=1;
        }
    };
    ~UnionFind(){}
    //木の根を求める
    int find(int x){
        if(par[x]==x) return x;
        return par[x]=find(par[x]);
    }
    //xとyの属する集合を併合
    void unite(int x,int y){
        x=find(x);
        y=find(y);
        if(x==y) return;
        quantity--;
        if(rank[x]<rank[y]){
            par[x]=y;
            scale[y]+=scale[x];
        }else{
            par[y]=x;
            scale[x]+=scale[y];
            if(rank[x]==rank[y]) rank[x]++;
        }
    }
    //xとyが同じ集合に属するか否か
    bool same(int x,int y){ return find(x)==find(y); }
    //xの属する集合のサイズ
    int size(int x){ return scale[find(x)]; }
    //木の個数
    int count(){ return quantity; }
};

int N,M;
int A[100000];
int B[100000];
ll C[100000];

void f(int v, int p, vector<int> &par, vector<vector<P>> &G){
    par[v]=p;
    repr(e,G[v]) if(e.first!=p){
        f(e.first,v,par,G);
    }
}

int main() {
    cin>>N>>M;
    rep(i,M){
        cin>>A[i]>>B[i]>>C[i];
        A[i]--, B[i]--;
    }

    vector<int> id(M);
    iota(all(id),0);
    sort(all(id),[&](int i, int j){ return C[i]<C[j]; });

    vector<vector<P>> G(N);
    vector<bool> use(N,0);
    UnionFind uf(N);
    ll cost=0;
    rep(i,M){
        int a=A[id[i]];
        int b=B[id[i]];
        int c=C[id[i]];
        if(!uf.same(a,b)){
            uf.unite(a,b);
            G[a].push_back({b,c});
            G[b].push_back({a,c});
            use[id[i]]=1;
            cost+=c;
        }
    }

    vector<int> par(N);
    f(0,-1,par,G);

    vector<ll> ans(M,cost);
    rep(i,M){
        if(!use[i]){
            ans[i]+=C[i];
            ll maxi=0;
            if()
            repr(e,G[A[i]]) maxi=max(maxi,e.second);
            repr(e,G[B[i]]) maxi=max(maxi,e.second);
            ans[i]-=maxi;
        }
    }

    repr(e,ans) cout<<e<<endl;
    
    return 0;
}