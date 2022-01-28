#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 5e3 + 5;

int n,m,a[N];
vector<int> G[N];int dfn[N][2],dfs_clk = 0;
int lim,val[N];
int num[N],cnta = 0,cntc = 0,ans[N];set<int> big[N];
int bl[N],bsz;

struct Qry{
    int idx,l,r;
    Qry(){}
    Qry(int i,int l,int r):idx(i),l(l),r(r){}
    bool operator < (const Qry &rh) const{
        return bl[l] ^ bl[rh.l] ? bl[l] < bl[rh.l] : r < rh.r;
    }
}q[N];

void dbg(){puts("");}
template<typename T, typename... R>void dbg(const T &f, const R &... r) {
    cout << f << " ";
    dbg(r...);
}
template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void dfs(int u,int ufa){
    dfn[u][0] = ++dfs_clk;
    for(int &v: G[u]){
        if(v == ufa) continue;
        dfs(v,u);
    }
    dfn[u][1] = dfs_clk;
}

void init(){
    rep(i,1,n) val[i] = a[i];
    sort(val+1,val+n+1);
    lim = unique(val+1,val+n+1)-val-1;
    rep(i,1,n) a[i] = lower_bound(val+1,val+lim+1,a[i]) - val;
    bsz = sqrt(n);
    rep(i,1,n) bl[i] = i / bsz + 1;
    dfs(1,0);
    vector<int> aa(n+1);
    rep(u,1,n) aa[dfn[u][0]] = a[u];
    rep(i,1,n) a[i] = aa[i];
}

inline void ad(int idx){
    int v = num[a[idx]];
    ++num[a[idx]];
    big[v].erase(a[idx]);
    big[v+1].insert(a[idx]);
    if(v+1 == cnta) cntc = *big[cnta].begin();
    if(v == cnta) ++cnta,cntc = *big[cnta].begin();
}

inline void dc(int idx){
    int v = num[a[idx]];
    --num[a[idx]];
    big[v].erase(a[idx]);
    big[v-1].insert(a[idx]);
    if(v == cnta){
        if(!big[cnta].size()) --cnta;
        cntc = *big[cnta].begin();
    }
}

void solve(){
    int L = 1,R = 0;
    rep(i,1,m){
        int ql = q[i].l,qr = q[i].r;
        while(R < qr) ad(++R);
        while(L > ql) ad(--L);
        while(R > qr) dc(R--);
        while(L < ql) dc(L++);
        ans[q[i].idx] = val[cntc];
    }
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
    read(m);
    rep(i,1,m){
        int x;read(x);q[i] = {i,dfn[x][0],dfn[x][1]};
    }
    sort(q+1,q+m+1);
    solve();
    rep(i,1,m) printf("%d\n",ans[i]);
    return 0;
}