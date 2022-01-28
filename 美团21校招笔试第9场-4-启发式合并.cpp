#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int SZ = 5e3 + 5;

int n,m,a[SZ];
vector<int> G[SZ];
int lim,val[SZ];
int son[SZ],siz[SZ];
int num[SZ],cnta = 0,cntc = 0,ans[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void init(){
    rep(i,1,n) val[i] = a[i];
    sort(val+1,val+n+1);
    lim = unique(val+1,val+n+1)-val-1;
    rep(i,1,n) a[i] = lower_bound(val+1,val+lim+1,a[i]) - val;
}

void change(int u){
    ++num[a[u]];
    if(num[a[u]] == cnta) cntc = min(cntc,a[u]);
    if(num[a[u]] > cnta){
        cnta++;cntc = a[u];
    }
}

void add(int u,int ufa){
    change(u);
    for(int v: G[u]) if(v != ufa) add(v,u);
}

void dec(int u,int ufa){
    --num[a[u]];cnta = cntc = 0;
    for(int &v: G[u]) if(v != ufa) dec(v,u);
}

void dfs1(int u,int ufa){
    siz[u] = 1;son[u] = 0;int mx = 0;
    for(int &v: G[u]){
        if(v == ufa) continue;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v] > mx) son[u] = v,mx = siz[v];
    }
}

void dfs2(int u,int ufa){
    for(int &v: G[u]){
        if(v == ufa || v == son[u]) continue;
        dfs2(v,u);
        dec(v,u);
    }
    if(son[u]) dfs2(son[u],u);
    for(int &v: G[u]){
        if(v == ufa || v == son[u]) continue;
        add(v,u);
    }
    change(u);
    ans[u] = val[cntc];
}

int main(int argc, char** argv) {
    read(n);
    re_(_,1,n){
        int x,y;read(x);read(y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    rep(i,1,n) read(a[i]);
    init();
    dfs1(1,0);
    dfs2(1,0);
    read(m);
    rep(i,1,m){
        int x;read(x);
        printf("%d\n",ans[x]);
    }
    return 0;
}