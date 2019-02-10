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
const int N = 1e5 + 5;
const int rx[4] = {1, 0, -1, 0};
const int ry[4] = {0, 1, 0, -1};
struct node {
    int sum = 0;
    int c_l, c_r;
    node():c_l(0), c_r(0), sum(0) {}
};
int n;
set < int > s[N];
vector < node > all;
vector < int > root;
int add_node() {
    all.pb(node());
    return sz(all) - 1;
}
int add_node(int v) {
    all.pb(all[v]);
    return sz(all) - 1;
}
void build(int v, int tl, int tr) {
    if (tl == tr) return;
    int p = add_node();
    all[v].c_l = p;
    p = add_node();
    all[v].c_r = p;
    int tm = (tl + tr) >> 1;
    build(all[v].c_l, tl, tm);
    build(all[v].c_r, tm + 1, tr);
}
int update (int v, int tl, int tr, int p, int x) {
    v = add_node(v);
    if (tl == tr) {
        all[v].sum += x;
        return v;
    }
    int tm = (tl + tr) >> 1;
    if (p <= tm) {
        int cur = update(all[v].c_l, tl, tm, p, x);
        all[v].c_l = cur;
    } else {
        int cur = update(all[v].c_r, tm + 1, tr, p, x);
        all[v].c_r = cur;
    }
    all[v].sum = all[all[v].c_l].sum + all[all[v].c_r].sum;
    return v;
}
int sum (int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (tl == l && tr == r) return all[v].sum;
    int tm = (tl + tr) >> 1;
    return sum(all[v].c_l, tl, tm, l, min(tm ,r)) +
        sum(all[v].c_r, tm + 1, tr, max(tm + 1, l), r);
}
int solve(int l, int r, int k) {
    int x = root[r], y = root[l - 1];
    int cl = 1, cr = N;
    while (cl < cr) {
        int mid = (cl + cr) >> 1;
        if (all[all[x].c_l].sum - all[all[y].c_l].sum < k) {
            k -= all[all[x].c_l].sum - all[all[y].c_l].sum;
            x = all[x].c_r;
            y = all[y].c_r;
            cl = mid + 1;
        } else {
            x = all[x].c_l;
            y = all[y].c_l;
            cr = mid;
        }
    }
    return cr;
}
signed main(){
//    freopen("input.txt","r",stdin);
//    freopen("output.txt","w",stdout);
    IOS
    add_node();
    root.pb(0);
    build(0, 1, N);
    int n, k;
    cin >> n >> k;
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int pr[n + 1] = {};
    for (int i = 1; i <= n; i++) {
        s[a[i]].insert(i);
        if (sz(s[a[i]]) == k + 1) {
            pr[i] = *s[a[i]].begin();
            s[a[i]].erase(s[a[i]].begin());
        }
        root.pb(update(root[i - 1], 0, n, pr[i], 1));
    }
    int m;
    cin >> m;
    int last = 0;
    for (int i = 0; i < m; i++) {
        int l, r, x, y;
        cin >> x >> y;
        l = ((x + last)%n) + 1;
        r = ((y + last)%n) + 1;
        if (l > r) swap(l, r);
        int now = sum(root[r], 0, n, 0, l - 1) - sum(root[l - 1], 0, n, 0, l - 1);
        last = now;
        cout << now << endl;
    }
}
