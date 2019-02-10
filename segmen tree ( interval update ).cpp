#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define IOS {ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);}
using namespace std;
int t[N*4], add[N*4], need[N*4];
void push(int v, int tl, int tr){
    if (need[v]){
        t[v] += add[v];
        if (tl != tr) {
            add[v * 2] += add[v];
            add[v * 2 + 1] += add[v];
            need[v * 2] = 1;
            need[v * 2 + 1] = 1;
        }
        need[v] = 0;
        add[v] = 0;
    }
}
void update(int v, int tl, int tr, int l, int r, int val) {
    push(v, tl, tr);
    if (l > r) return;
    if (tl == l && tr == r) {
        add[v] += val;
        need[v] = 1;
        push(v, tl, tr);
        return;
    }
    int tm = (tl + tr)/2;
    update(v * 2, tl, tm, l, min(tm, r), val);
    update(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
}
int ma(int v, int tl, int tr, int l, int r){
    push(v, tl, tr);
    if (l > r) return -tinf;
    if (tl == l && tr == r){
        return t[v];
    }
    int tm = (tl + tr)/2;
    return max(ma(v * 2, tl, tm, l, min(tm, r)),
               ma(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
}
