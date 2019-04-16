#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define sz(a) (int)a.size()
#define pb push_back

using namespace std;

const int N = (int)5e5 + 5;
const int tinf = (int)1e9 + 7;
const long long M = (long long) 1e9 + 37;
const long long inf = (long long) 1e18 + 7;

struct Node {
    int div, cnt;
};
vector < Node > v[(int)1e6 + 1];
vector < int > res[(int)1e6 + 1];
int cnt[(int)1e6 + 1];
int lp[(int)1e6 + 1];
int now, cur = 0;
vector < int > vv;

inline void solve(int x, int pos) {
    if (pos == sz(v[x])) {
        res[x].pb(now);
        return;
    }
    for (int i = 0; i <= v[x][pos].cnt; i++) {
        solve(x, pos + 1);
        if (i != v[x][pos].cnt)
            now *= v[x][pos].div;
    }
    for (int i = 0; i < v[x][pos].cnt; i++) {
        now /= v[x][pos].div;
    }
}

signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n = (int)1e6;
    vector < int > pr;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; ++j)
            lp[i * pr[j]] = pr[j];
    }
    for (int i = 2; i <= n; i++) {
        int x = i;
        while (x != 1) {
            if (v[i].empty() || lp[x] != v[i].back().div) {
                v[i].pb({lp[x], 0});
            }
            x /= lp[x];
            v[i].back().cnt++;
        }
    }
    for (int i = 2; i <= n; i++) {
        now = 1, cur = 0;
        solve(i, 0);
    }
    int m;
    cin >> m;
    int a[m];
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    sort(a, a + m);
    long long ans = 0;
    res[1].pb(1);
    for (int i = 0; i < m; i++) {
        for (auto j : res[a[i]]) {
            ans += cnt[j];
        }
        cnt[a[i]]++;
    }
    cout << ans;
}
