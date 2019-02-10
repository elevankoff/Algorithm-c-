#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define F first
#define S second
//#define int long long
#define ld long double
#define sz(a) (int)a.size()
#define endl '\n'
#define IOS {ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);}
#define TIME 1.0*clock()/CLOCKS_PER_SEChttps:
#define pb push_back
using namespace std;
const int tinf = (int)1e9 + 7;
const long long inf = (long long)1e18 + 7;
const int N = 1e6 + 5;
const int rx[4] = {1, 0, -1, 0};
const int ry[4] = {0, 1, 0, -1};
int metka[N], t[N*4], add[N*4], need[N*4];
set < int > pos[N];
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
signed main(){
    freopen("different.in","r",stdin);
    freopen("different.out","w",stdout);
    IOS
    int n, m, k;
    cin >> n >> m >> k;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].insert(i);
    }
    int now = 0;
    for (int i = 0; i < k; i++) {
        if (!metka[a[i]]) {
            now++;
        }
        metka[a[i]]++;
    }
    int cnt[n - k + 1] = {};
    cnt[0] = now;
    for (int i = k; i < n; i++) {
        if (metka[a[i - k]] == 1) now--;
        metka[a[i - k]]--;

        if (!metka[a[i]]) now++;
        metka[a[i]]++;

        cnt[i - k + 1] = now;
    }
    for (int i = 0; i <= n - k; i++) {
        update(1, 0, n - k, i, i, cnt[i]);
    }
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j, x;
            cin >> j >> x;
            j--;

            set < int > :: iterator itr = pos[a[j]].lower_bound(j),
                itl;
            int l, r;
            itr++;
            if (itr == pos[a[j]].end()) {
                r = min(n - k, j);
            } else r = min(j, *itr - k);
            itr--;
            if (itr == pos[a[j]].begin()) {
                l = max(0, j - k + 1);
            } else {
                itl = itr;
                itl--;
                l = max(j - k + 1, *itl + 1);
            }
            if (l <= r) update(1, 0, n - k, l, r, -1);
            pos[a[j]].erase(j);
            a[j] = x;
            pos[a[j]].insert(j);

            itr = pos[a[j]].lower_bound(j);
            itr++;
            if (itr == pos[a[j]].end()) {
                r = min(n - k, j);
            } else r = min(j, *itr - k);
            itr--;
            if (itr == pos[a[j]].begin()) {
                l = max(0, j - k + 1);
            } else {
                itl = itr;
                itl--;
                l = max(j - k + 1, *itl + 1);
            }
            if (l <= r) update(1, 0, n - k, l, r, 1);
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            r = r - k + 1;
            cout << ma(1, 0, n - k, l, r) << endl;
        }
    }
}
