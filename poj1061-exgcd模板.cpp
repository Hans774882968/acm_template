#include <cstdio>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 30 + 5;

int x,y,m,n,L;

// void dbg(){puts("");}
// template<typename T, typename... R>void dbg(const T &f, const R &... r) {
    // cout << f << " ";
    // dbg(r...);
// }
template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;return a;
    }
    int g = exgcd(b,a%b,y,x);
    y -= a/b*x;
    return g;
}

int gcd(int a,int b){return !b ? a : gcd(b,a%b);}

int main(int argc, char** argv) {
    read(x);read(y);read(m);read(n);read(L);
    int a = ((m-n) % L + L) % L,b = y-x;
    if(b % gcd(a,L)){
        puts("Impossible");return 0;
    }
    int c,d;
    int g = exgcd(a,L,c,d);
    int ans = (1LL*c*(b/g) % (L/g) + (L/g)) % (L/g);
    printf("%d\n",ans);
    return 0;
}