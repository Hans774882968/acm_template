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
#include <stack>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int SZ = 1e5 + 5;

int n,m;

template<typename Type>inline void read(Type &xx){
    Type f = 1;char ch;xx = 0;
    for(ch = getchar();ch < '0' || ch > '9';ch = getchar()) if(ch == '-') f = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()) xx = xx * 10 + ch - '0';
    xx *= f;
}

int tot = 0;
#define get_sz(p) (!(p) ? 0 : (p)->sz)
struct Node{
    int sz,x,rk,rev;
    Node *ls,*rs;
    
    void pushdown(){
        if(!rev) return;
        if(ls) ls->rev ^= 1;
        if(rs) rs->rev ^= 1;
        swap(ls,rs);
        rev = 0;
    }
    
    void pushup(){sz = 1 + get_sz(ls) + get_sz(rs);}
}pool[SZ << 1],*rt;
Node* newnode(int x){
    Node *p = pool + (++tot);
    p->x = x;
    p->rk = rand();
    p->rev = 0;
    p->sz = 1;
    return p;
}
void split(Node *p,Node *&pL,Node *&pR,int k){
    if(!p){
        pL = pR = NULL;
        return;
    }
    p->pushdown();
    int szL = get_sz(p->ls);
    if(szL < k){
        pL = p;
        split(p->rs,pL->rs,pR,k - szL - 1);
    }
    else{
        pR = p;
        split(p->ls,pL,pR->ls,k);
    }
    if(pL) pL->pushup();
    if(pR) pR->pushup();
}
void merge(Node *&p,Node *pL,Node *pR){
    if(!pL || !pR){
        p = pL ? pL : pR;
        return;
    }
    pL->pushdown();
    pR->pushdown();
    if(pL->rk < pR->rk){
        p = pL;
        merge(p->rs,pL->rs,pR);
    }
    else{
        p = pR;
        merge(p->ls,pL,pR->ls);
    }
    p->pushup();
}
void insert(int x){
    Node *p1,*p2;
    split(rt,p1,p2,x - 1);
    merge(rt,p1,newnode(x));
    merge(rt,rt,p2);
}
void del(int x){
    Node *p1,*p2,*p3,*p4;
    split(rt,p1,p2,x - 1);
    split(p2,p3,p4,1);
    merge(rt,p1,p4);
}
void reverse(int l,int r){
    Node *p1,*p2,*p3,*p4;
    split(rt,p1,p2,l - 1);
    split(p2,p3,p4,r - l + 1);
    p3->rev ^= 1;
    merge(p2,p3,p4);
    merge(rt,p1,p2);
}

void print(Node *p){
    if(!p) return;
    p->pushdown();
    print(p->ls);
    printf("%d ",p->x);
    print(p->rs);
}

int main(int argc, char** argv) {
    read(n);read(m);
    for(int i = 1;i <= n;i++) insert(i);
    for(int i = 1;i <= m;i++){
        int l,r;read(l);read(r);
        reverse(l,r);
    }
    print(rt);puts("");
    getchar();getchar();
    return 0;
}
