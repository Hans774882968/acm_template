#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int SZ = 5e5 + 5;

char s[SZ];int L[SZ],R[SZ];stack<int> sk;
int n,sa[SZ],rk[SZ << 1],tmprk[SZ << 1],bucket[SZ],y[SZ],ht[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void get_sa(int sl){
    int limit = 1 << 7;
    memset(bucket,0,sizeof bucket);
    for(int i = 1;i <= sl;i++) rk[i] = s[i],bucket[rk[i]]++;
    for(int i = 1;i <= limit;i++) bucket[i] += bucket[i-1];
    for(int i = sl;i >= 1;i--) sa[bucket[rk[i]]--] = i;
    for(int k = 1;k < sl;k <<= 1){
        memset(bucket,0,sizeof bucket);
        int pos = 0;dwn(i,sl,sl-k+1) y[++pos] = i;
        for(int i = 1;i <= sl;i++) if(sa[i] - k >= 1) y[++pos] = sa[i] - k;
        for(int i = 1;i <= sl;i++) bucket[rk[y[i]]]++;
        for(int i = 1;i <= limit;i++) bucket[i] += bucket[i-1];
        for(int i = sl;i >= 1;i--) sa[bucket[rk[y[i]]]--] = y[i];
        memcpy(tmprk,rk,sizeof tmprk);
        rk[sa[1]] = 1;
        for(int i = 2,cnt = 1;i <= sl;i++) rk[sa[i]] = (tmprk[sa[i-1]] == tmprk[sa[i]] && tmprk[sa[i-1]+k] == tmprk[sa[i]+k]) ? cnt : ++cnt;
        limit = pos;
    }
    for(int i = 1,k = 0;i <= n;++i){
        if(k) --k;
        while(s[i+k] == s[sa[rk[i]-1]+k]) ++k;
        ht[rk[i]] = k;
    }
}

LL lcp_tot(){
    LL ret = 0;
    rep(i,2,n) ret += 1LL*(i-L[i])*(R[i]-i)*ht[i];
    return ret * 2;
}

int main(int argc, char** argv) {
    scanf("%s",s+1);
    n = strlen(s+1);
    get_sa(n);
    rep(i,2,n){
        while(!sk.empty() && ht[sk.top()] > ht[i]) sk.pop();
        L[i] = sk.empty() ? 1 : sk.top();
        sk.push(i);
    }
    while(!sk.empty()) sk.pop();
    dwn(i,n,2){
        while(!sk.empty() && ht[sk.top()] >= ht[i]) sk.pop();
        R[i] = sk.empty() ? n+1 : sk.top();
        sk.push(i);
    }
    LL ans = 0;
    rep(i,2,n) ans += 1LL*i*(i-1)/2 + 1LL*i*(i-1);
    ans -= lcp_tot();
    printf("%lld\n",ans);
    return 0;
}