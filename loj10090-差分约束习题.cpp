#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int SZ = 100000 + 3,INF = 1e9 + 10;

int n,m1,m2;
int dis[SZ],tot[SZ];bool vis[SZ];queue<int> q;

int head[SZ],en = 0;
struct Edge{
    int to,w,nxt;
    Edge(){}
    Edge(int to,int w,int nxt):to(to),w(w),nxt(nxt){}
}e[SZ << 1];
void addedge(int p1,int p2,int w){
    e[en] = Edge(p2,w,head[p1]);head[p1] = en++;
}

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

bool spfa(int S){
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof vis);memset(tot,0,sizeof tot);
    for(int i = 1;i <= n;++i) dis[i] = INF;
    dis[S] = 0;vis[S] = true;tot[S] = 1;q.push(S);
    while(!q.empty()){
        int u = q.front();q.pop();
        vis[u] = false;
        for(int i = head[u];~i;i = e[i].nxt){
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].w){
                dis[v] = dis[u] + e[i].w;
                if(!vis[v]){
                    vis[v] = true;
                    if(++tot[v] > n) return false;
                    q.push(v);
                }
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    while(~scanf("%d%d%d",&n,&m1,&m2)){
        en = 0;memset(head,-1,sizeof head);
        for(int i = 0;i < m1;++i){
            int p1,p2,w;read(p1);read(p2);read(w);
            addedge(p1,p2,w);
        }
        for(int i = 0;i < m2;++i){
            int p1,p2,w;read(p1);read(p2);read(w);
            addedge(p2,p1,-w);
        }
        int S = n + 1;
        for(int i = 1;i <= n;++i) addedge(S,i,0);
        if(!spfa(S) || !spfa(1)){
            puts("-1");
            continue;
        }
        int ans = dis[n];
        if(ans >= INF) puts("-2");
        else printf("%d\n",ans);
    }
    return 0;
}