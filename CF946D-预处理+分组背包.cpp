#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int SZ = 505;

int n,m,k;
char s[SZ][SZ];
int dp[SZ],val[SZ][SZ],valen[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void getVal(int i,int les[],int tot){
    valen[i] = tot;
    re_(j,0,tot){
        int mn = m;
        for(int l = 1,r;(r = l + tot - j - 1) <= tot;++l)
            mn = min(mn,les[r] - les[l] + 1);
        val[i][j] = mn;
    }
    re_(j,0,tot) val[i][j] = m - val[i][j];
    val[i][tot] = m;
}

int main(int argc, char** argv) {
    while(~scanf("%d%d%d",&n,&m,&k)){
        rep(i,1,n) scanf("%s",s[i] + 1);
        memset(dp,0,sizeof dp);
        rep(i,1,n) valen[i] = 0;
        rep(i,1,n){
            int hd = 1,tl = 0,les[SZ];
            rep(j,1,m){
                if(s[i][j] != '1') continue;
                les[++tl] = j;
            }
            getVal(i,les,tl);
        }
        rep(i,1,n){
            dwn(j,k,0){
                rep(v,0,min(valen[i],j)){
                    dp[j] = max(dp[j],dp[j - v] + val[i][v]);
                }
            }
        }
        printf("%d\n",n * m - dp[k]);
    }
    return 0;
}