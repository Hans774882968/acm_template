#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 1e5 + 5;

int n,a[N<<1],ps[N<<1];

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

int main(int argc, char** argv) {
    int T;read(T);
    while(T--){
        read(n);
        rep(i,1,n) read(a[i]);
        re_(i,1,n) a[n+i] = a[i];
        n = 2*n-1;
        rep(i,1,n) ps[i] = ps[i-1]+a[i];
        deque<int> q;
        q.push_back(0);
        int ans = 0;
        rep(i,2,n){
            while(!q.empty() && q.front() < i-(n+1)/2) q.pop_front();
            ans = max(ans,ps[i]-ps[q.front()]);
            while(!q.empty() && ps[q.back()] > ps[i]) q.pop_back();
            q.push_back(i);
        }
        printf("%d\n",ans);
    }
    return 0;
}