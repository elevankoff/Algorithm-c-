#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define ld long double
#define int long long
#define F first
#define S second
#define sz(a) (int)a.size()
#define endl '\n'
#define IOS {ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);}
#define pb push_back
#define pi 3.1415926535897932384626433832795
using namespace std;
const int tinf = (int)1e9 + 7;
const long long inf = (long long)1e18 + 7;
const int N = 5e5 + 5;
const long long M = 1e9 + 7;
const int rx[4] = {1, 0, -1, 0};
const int ry[4] = {0, 1, 0, -1};

int cnt[20][2];
int a[N], ans;
int Size[N];
bool used[N];
vector < int > g[N];

void dfs (int v, int pr) {
    Size[v] = 1;
    for (auto to : g[v]) {
        if (to != pr && !used[to]) {
            dfs(to, v);
            Size[v] += Size[to];
        }
    }
}

int centroid (int v) {
    int need = Size[v] / 2;
    int pr = -1;
    bool run = 1;
    while (run) {
        run = 0;
        for (auto to : g[v]) {
            if (to != pr && !used[to]) {
                if (Size[to] > need) {
                    pr = v;
                    v = to;
                    run = 1;
                    break;
                }
            }
        }
    }
    return v;
}

void add (int v, int pr, int x) {
    for (int i = 0; i < 20; i++) {
        cnt[i][(x >> i)%2]++;
    }
    for (auto to : g[v]) {
        if (to != pr && !used[to]) {
            add(to, v, x ^ a[to]);
        }
    }
}

void get (int v, int pr, int x) {
    for (int i = 0; i < 20; i++) {
        ans += (1 << i) * cnt[i][1 ^ ((x >> i)%2)];
    }
    for (auto to : g[v]) {
        if (to != pr && !used[to]) {
            get(to, v, x ^ a[to]);
        }
    }
}

int solve (int v) {
    dfs(v, v);
    int c = centroid (v);
    for (int i = 0; i < 20; i++) {
        cnt[i][0] = cnt[i][1] = 0;
        cnt[i][(a[c] >> i)%2]++;
    }
    ans += a[c];
    for (auto to : g[c]) {
        if (!used[to]) {
            get(to, c, a[to]);
            add(to, c, a[c] ^ a[to]);
        }
    }
    used[c] = true;
    for (auto to : g[c]) {
        if (!used[to]) solve(to);
    }
}

signed main() {
//  freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    IOS
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> v >> u;
        v--;
        u--;
        g[v].pb(u);
        g[u].pb(v);
    }
    solve(0);
    cout << ans;
}
