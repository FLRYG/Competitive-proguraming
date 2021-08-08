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
typedef pair<int,int> P;
typedef pair<int,P> IP;
// typedef pair<P,P> PP;
double const PI=3.141592653589793;
int const INF=1001001001;
ll const LINF=1001001001001001001;
ll const MOD=1000000007;

int const I[]={1,0,-1,0};
int const J[]={0,1,0,-1};
int const I2[]={1,1,0,-1,-1,-1,0,1,0};
int const J2[]={0,1,1,1,0,-1,-1,-1,0};

int H,W;
char S[500][500];

int main(){
    cin>>H>>W;
    rep(i,H) rep(j,W) cin>>S[i][j];

    vector<vector<int>> cost(H,vector<int>(W,INF));
    priority_queue<IP,vector<IP>,greater<IP>> q;
    q.push({0,{0,0}});
    while(!q.empty()){
        IP ip=q.top(); q.pop();
        int c=ip.first;
        int i=ip.second.first;
        int j=ip.second.second;
        if(cost[i][j]<=c) continue;
        cost[i][j]=c;
        rep(k,4){
            int x=i+I[k];
            int y=j+J[k];
            if(0<=x && x<H && 0<=y && y<W){
                if(S[x][y]=='.'){
                    if(c<cost[x][y]) q.push({c,{x,y}});
                }else{
                    rep(l,9){
                        int x2=x+I2[l];
                        int y2=y+J2[l];
                        if(0<=x2 && x2<H && 0<=y2 && y2<W && c+1<cost[x2][y2]){
                            q.push({c+1,{x2,y2}});
                        }
                    }
                }
            }
        }
    }

    // rep(i,H){
    //     rep(j,W) cout<<cost[i][j]<<' ';
    //     cout<<endl;
    // }

    cout<<cost[H-1][W-1]<<endl;
    
    return 0;
}