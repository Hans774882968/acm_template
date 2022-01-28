#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 100 + 5,M = 3005;
const LL INF = 1e9 + 7;

vector<pair<int,int> > G[N];
int n,m;
int e[M][2],pre[N][N];
bool vis[N];LL dis[N][N],sum[N];
queue<int> q;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

LL bfs(int st,int ei){//ei是禁止边
    q.push(st);
    memset(vis,0,sizeof vis);vis[st] = true;
    rep(i,1,n) pre[st][i] = 0,dis[st][i] = INF;dis[st][st] = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(auto x: G[u]){
            int v = x.first;
            if(vis[v]) continue;
            if(ei == x.second) continue;
            vis[v] = true;pre[st][v] = u;
            dis[st][v] = dis[st][u] + 1;
            q.push(v);
        }
    }
    sum[st] = 0;
    rep(i,1,n) sum[st] += dis[st][i];
    return sum[st];
}

int main(int argc, char** argv) {
    while(~scanf("%d%d",&n,&m)){
        rep(i,1,n) G[i].clear();
        rep(i,1,m){
            read(e[i][0]);read(e[i][1]);
            G[e[i][0]].push_back({e[i][1],i});
            G[e[i][1]].push_back({e[i][0],i});
        }
        LL ans = 0;
        rep(i,1,n) ans += bfs(i,-1);
        rep(i,1,m){
            int u = e[i][0],v = e[i][1];
            LL ta = ans;
            rep(j,1,n){
                if(pre[j][v] == u || pre[j][u] == v){
                    ta -= sum[j];
                    LL ts = sum[j];
                    ta += bfs(j,i);
                    sum[j] = ts;
                }
            }
            if(ta < INF) printf("%lld\n",ta);
            else puts("INF");
        }
    }
    return 0;
}