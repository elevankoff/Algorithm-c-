#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define ld long double
#define ll long long
#define F first
#define S second
#define mp make_pair
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

struct Query {
    int L, R, Time, Num;
    Query (int x) : L(0), R(0), Time(0), Num(x) {}
};

struct Update {
    int pos, val;
    Update () : pos(0), val(0) {}
    Update (int _pos, int _val) : pos(_pos), val(_val) {}
};

Update updates[N];
int a[N];
int B;
vector < int > all[N];
int Cnt[N];
bool In[N];
int nowTime = 0;
vector < int > q;

bool comp (Query a, Query b) {
    if (a.L / B == b.L / B) {
        if (a.R / B == b.R / B) {
            return a.Time < b.Time;
        }
        return a.R / B < b.R / B;
    }
    return a.L / B < b.L / B;
}

void Add (int x) {
    Cnt[x]++;
    if (Cnt[x] == 1 && !In[x]) {
        In[x] = 1;
        q.pb(x);
    }
}

void Delete (int x) {
    Cnt[x]--;
    if (Cnt[x] == 1 && !In[x]) {
        In[x] = 1;
        q.pb(x);
    }
}

void Update_Delete (int nowTime, int l, int r) {
    int pos = updates[nowTime].pos, val = updates[nowTime].val;
    if (pos >= l && pos <= r) {
        Delete(val);
    }
    if (!all[pos].empty()) all[pos].pop_back();
    if (pos >= l && pos <= r) {
        if (!all[pos].empty()) Add(all[pos].back());
    }
}

void Update_Add (int nowTime, int l, int r) {
    int pos = updates[nowTime].pos, val = updates[nowTime].val;
    if (pos >= l && pos <= r) {
        if (!all[pos].empty()) Delete(all[pos].back());
        Add(val);
    }
    all[pos].pb(val);
}

int getAnswer () {
    while (!q.empty() && Cnt[q.back()] != 1) {
        In[q.back()] = 0;
        q.pop_back();
    }
    return q.empty() ? -1 : q.back();
}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    IOS
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        all[i].pb(a[i]);
    }
    B = pow(n, 2.0 / 3.0);
    int q;
    cin >> q;
    vector < Query > queries;
    int CntUpdates = 0;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            queries.pb(Query(sz(queries)));
            cin >> queries.back().L >> queries.back().R;
            queries.back().L--;
            queries.back().R--;
            queries.back().Time = CntUpdates;
        } else {
            int pos, val;
            cin >> pos >> val;
            updates[CntUpdates++] = Update(pos - 1, val);
        }
    }
    sort(queries.begin(), queries.end(), comp);
    int l = 1, r = 0;
    int was = 0;
    int ans[sz(queries)] = {};
    for (auto query : queries) {
        while (nowTime < query.Time) Update_Add(nowTime++, l, r);
        while (nowTime > query.Time) Update_Delete(--nowTime, l, r);
        while (l > query.L) Add(all[--l].back());
        while (r < query.R) Add(all[++r].back());
        while (l < query.L) Delete(all[l++].back());
        while (r > query.R) Delete(all[r--].back());
        ans[query.Num] = getAnswer();
    }
    for (int i = 0; i < sz(queries); i++) {
        cout << ans[i] << endl;
    }
}
