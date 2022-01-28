#include <cstdio>
using namespace std;
typedef long long LL;
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define re_(i,a,b) for(int i = (a);i < (b);++i)
#define dwn(i,a,b) for(int i = (a);i >= (b);--i)

const int N = 30 + 5;

int n;

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

int euler(int x){
    int ans = 1;
    for(int i = 2;i <= x/i;++i){
        if(x % i) continue;
        int c = 1;
        x /= i;
        while(!(x % i)) c *= i,x /= i;
        ans *= c*(i-1);
    }
    if(x > 1) ans *= x-1;
    return ans;
}

int main(int argc, char** argv) {
    while(~scanf("%d",&n) && n){
        printf("%d\n",euler(n));
    }
    return 0;
}