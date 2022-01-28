#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 2e5 + 5;
const int mod = 1e9 + 7;

int n,k,x,mu[N];
int q[N],lim;//离线
LL f[N],g[N],pw[N];
bool vis[N];vector<int> primes;

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

LL q_pow(LL a,LL b){
    LL ret = 1;
    for(;b;b >>= 1){
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
    }
    return ret;
}

void init_primes(int n){
    vis[1] = true;mu[1] = 1;
    rep(i,2,n){
        if(!vis[i]) primes.push_back(i),mu[i] = -1;
        for(int p: primes){
            if(i > n / p) break;
            vis[i * p] = true;
            if(i % p == 0) break;
            mu[i * p] = -mu[i];
        }
    }
}

void init(int n){
    init_primes(n);
    for(int s = 0,i = 1;i <= n;++i){
        (s += q_pow(i,k)) %= mod;
        f[i] = q_pow(s,x);
    }
    rep(i,1,n)
        rep(j,1,n/i)
            g[i*j] += mu[i]*mu[i]*mu[j]*i;
    rep(i,1,n) g[i] = (g[i] % mod + mod) % mod;
    int pnum = 1LL * x * k % (mod - 1);
    rep(i,1,n) pw[i] = q_pow(i,pnum);
    rep(i,1,n) g[i] = g[i] * pw[i] % mod;
    rep(i,1,n) g[i] = (g[i] + g[i-1]) % mod;
}

int main(int argc, char** argv) {
    int T;read(T);read(k);read(x);
    lim = 0;rep(i,1,T) read(q[i]),lim = max(lim,q[i]);
    init(lim);
    rep(t,1,T){
        n = q[t];
        LL ans = 0;
        for(int L = 1,R;L <= n;L = R+1){
            R = n/(n/L);
            (ans += ((g[R]-g[L-1]+mod)%mod) * f[n/L] % mod) %= mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}