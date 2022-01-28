#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 1e6 + 5;
const int lim = 1e9 + 7;//主席树的区间上限

int n,m,a[N];
int rt[N],cnt = 0;

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

struct Node{
    LL v;int l,r;
    Node(){v = l = r = 0;}
}nod[N * 40];//log(1e9)

void modify(int &ti,int tj,int l,int r,int idx,int v){
    nod[ti = ++cnt] = nod[tj];nod[ti].v += v;
    if(l == r) return;
    int mid = (l+r)>>1;
    if(idx <= mid) modify(nod[ti].l,nod[tj].l,l,mid,idx,v);
    else modify(nod[ti].r,nod[tj].r,mid+1,r,idx,v);
}

LL getsum(int ti,int tj,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return nod[ti].v - nod[tj].v;
    int mid = (l+r)>>1;
    LL ret = 0;
    if(ql <= mid) ret += getsum(nod[ti].l,nod[tj].l,l,mid,ql,qr);
    if(qr > mid) ret += getsum(nod[ti].r,nod[tj].r,mid+1,r,ql,qr);
    return ret;
}

int main(int argc, char** argv) {
    read(n);read(m);
    rep(i,1,n) read(a[i]);
    rep(i,1,n){
        modify(rt[i],rt[i-1],1,lim,a[i],a[i]);
    }
    LL ans = 0;
    while(m--){
        int l,r;read(l);read(r);
        l = (l+ans) % n + 1;r = (r+ans) % n + 1;
        if(l > r) swap(l,r);
        ans = 0;
        while(true){
            LL t = ans;
            //min(ans+1,lim)防止nod[]访问越界
            ans = getsum(rt[r],rt[l-1],1,lim,1,min(ans+1,1LL*lim));
            if(ans == t) break;
        }
        ++ans;
        printf("%lld\n",ans);
    }
    return 0;
}