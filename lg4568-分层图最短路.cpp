#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int SZ = 1e5 + 5;
const LL INF = (1LL << 60) + 10;

int n,m,k;
LL dis[SZ][12];bool vis[SZ][12];

struct Node{
    int x;LL d;int k;//使用了k次
    Node(){}
    Node(int x,LL d,int k):x(x),d(d),k(k){}
    bool operator < (const Node &rhs) const{
        return d > rhs.d;
    }
};
priority_queue<Node> q;

int en = 0,head[SZ];
struct Edge{
    int to,w,nxt;
    Edge(){}
    Edge(int to,int w,int nxt):to(to),w(w),nxt(nxt){}
}e[SZ * 6];
void addedge(int p1,int p2,int w){
    e[en] = Edge(p2,w,head[p1]);head[p1] = en++;
}

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void dij(int S,int n){
    rep(i,1,n) rep(j,0,k) dis[i][j] = INF;
    memset(vis,0,sizeof vis);
    dis[S][0] = 0;q.push(Node(S,0,0));
    while(!q.empty()){
        Node x = q.top();q.pop();
        int u = x.x,uk = x.k;LL ud = x.d;
        if(vis[u][uk]) continue;
        vis[u][uk] = true;
        for(int i = head[u];i != -1;i = e[i].nxt){
            int v = e[i].to;
            if(uk < k && dis[v][uk+1] > ud){//易错：忘记uk<k可能造成越界！
                dis[v][uk+1] = ud;
                q.push(Node(v,ud,uk+1));
            }
            if(dis[v][uk] > ud + e[i].w){
                dis[v][uk] = ud + e[i].w;
                q.push(Node(v,dis[v][uk],uk));
            }
        }
    }
}

int main(int argc, char** argv) {
    int S,T;
    while(~scanf("%d%d%d%d%d",&n,&m,&k,&S,&T)){
        memset(head,-1,sizeof head);en = 0;++S,++T;
        rep(i,1,m){
            int x,y,w;read(x);read(y);read(w);++x,++y;
            addedge(x,y,w);addedge(y,x,w);
        }
        dij(S,n);
        LL ans = INF;
        rep(i,0,k) ans = min(ans,dis[T][i]);
        printf("%lld\n",ans);
    }
    return 0;
}