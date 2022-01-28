#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int SZ = 200000 + 3,INF = 1e9 + 10;

int n,m,S;vector<int> G[SZ];
int dis[SZ];queue<int> q;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

void bfs(int S){
    set<int> acc,ncc;
    for(int i = 1;i <= n;++i){
        dis[i] = INF;
        if(i != S) acc.insert(i);
    }
    dis[S] = 0;q.push(S);
    while(!q.empty()){
        int u = q.front();q.pop();
        for(auto v: G[u]){
            if(!acc.count(v)) continue;
            acc.erase(v);
            ncc.insert(v);
        }
        for(auto v: acc){
            dis[v] = dis[u] + 1;
            q.push(v);
        }
        acc.swap(ncc);
        ncc.clear();
    }
}

int main(int argc, char** argv) {
    int T;read(T);
    while(~scanf("%d%d",&n,&m)){
        for(int i = 1;i <= n;++i) G[i].clear();
        for(int i = 0;i < m;++i){
            int p1,p2;read(p1);read(p2);
            G[p1].push_back(p2);G[p2].push_back(p1);
        }
        read(S);
        bfs(S);
        for(int i = 1;i <= n;++i) if(i != S) printf("%d%c",dis[i] < INF ? dis[i] : -1," \n"[i == n]);
    }
    return 0;
}