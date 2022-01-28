#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int SZ = 5000 + 5,MD = 5001;

int n,m;
vector<int> G[SZ];
queue<int> q;bool vis[SZ];int deg[SZ];
int cnt = 0,tmpa[SZ],ans[SZ];set<int> tg;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void topo(){
    for(int i = 1;i <= n;i++) if(deg[i] == 1) q.push(i),vis[i] = true;
    while(!q.empty()){
        int u = q.front();q.pop();
        vis[u] = true;
        for(auto v: G[u]){
            if(vis[v]) continue;
            deg[v]--;
            if(deg[v] == 1) q.push(v),vis[v] = true;
        }
    }
}

void dfs(int u,int ufa,int p1,int p2){
    if(ufa <= 0) cnt = 0;
    tmpa[++cnt] = u;
    for(auto v: G[u]){
        if(v == ufa || (u == p1 && v == p2) || (v == p1 && u == p2)) continue;
        dfs(v,u,p1,p2);
    }
}

void better(){
    if(ans[1] > 0){
        for(int i = 1;i <= n;i++){
            if(tmpa[i] == ans[i]) continue;
            else if(tmpa[i] > ans[i]) return;
            else break;
        }
    }
    for(int i = 1;i <= n;i++) ans[i] = tmpa[i];
}

void print(){
    for(int i = 1;i <= n;i++) printf("%d ",ans[i]);
    puts("");
}

int main(int argc, char** argv) {
    read(n);read(m);
    for(int i = 1;i <= m;i++){
        int p1,p2;read(p1);read(p2);
        G[p1].push_back(p2);G[p2].push_back(p1);
        deg[p1]++;deg[p2]++;
    }
    for(int i = 1;i <= n;i++) sort(G[i].begin(),G[i].end());
    if(m == n - 1){
        dfs(1,0,0,0);
        better();
        print();
        return 0;
    }
    topo();
    for(int i = 1;i <= n;i++){
        for(auto v: G[i]){
            if(vis[i] || vis[v]) continue;
            int n1 = i,n2 = v;if(n1 > n2) swap(n1,n2);
            tg.insert(n1 * MD + n2);
        }
    }
    for(auto it: tg){
        dfs(1,0,it / MD,it % MD);
        better();
    }
    print();
    return 0;
}
