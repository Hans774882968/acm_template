#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
//#include <cmath>
#include <queue>
#include <map>
#include <cassert>
#include <set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int SZ = 3000 + 5;

int n,K,ans;char s[SZ];
int fail[SZ];bool vis[SZ];

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void get_fail(char t[],int tl){
    fail[0] = -1;
    rep(j,1,tl){
        int k = fail[j - 1];
        while(~k && t[k] != t[j - 1]) k = fail[k];
        fail[j] = k + 1;
    }
    for(int i = tl;i >= K;i--){
        if(vis[i]) continue;
        int j;for(j = i;fail[j] >= K;j = fail[j]);
        for(int k = i;fail[k] >= K;k = fail[k]){
            if(k - 2 * j <= 0) break;
            if(!vis[k]){
                ++ans;
                vis[k] = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    int T;read(T);
    while(T--){
        scanf("%s",s + 1);
        read(K);
        n = strlen(s + 1);
        ans = 0;
        rep(i,1,n){
            rep(j,0,n - i + 1) vis[j] = false;
            get_fail(s + i,n - i + 1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
