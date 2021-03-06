#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define ld long double
#define ll long long
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

// С ОДНОЙ ЛИ СТОРОНЫ ПРЯМОЙ ЛЕЖАТ ДВЕ ТОЧКИ
inline bool one_side (ll x1, ll y1, ll x2, ll y2, ll A, ll B, ll C) {
    ll z1 = A*x1 + B*y1 + C, z2 = A*x2 + B*y2 + C;
    return (z1 * z2 >= 0);
}

// ТОЧКА НА ПРЯМОЙ ИЛИ НЕТ
inline bool dot_on_line (ll A, ll B, ll C, ll x, ll y) {
    return (A*x + B*y + C == 0);
}

// ТОЧКА НА ПРЯМОЙ ИЛИ НЕТ
inline bool dot_on_line (ll x1, ll y1, ll x2, ll y2, ll x, ll y) {
    ld A = y2 - y1, B = x1 - x2, C = y1*x2 - x1*y2;
    return dot_on_line(A, B, C, x, y);
}

// РАССТОЯНИЕ ОТ ТОЧКИ ДО ПРЯМОЙ
inline ld dist_dot_line (ld A, ld B, ld C, ld x, ld y) {
    return fabs(A*x + B*y + C)/sqrt(A*A + B*B);
}

// РАССТОЯНИЕ ОТ ТОЧКИ ДО ПРЯМОЙ
inline ld dist_dot_line (ld x1, ld y1, ld x2, ld y2, ld x, ld y) {
    ld A = y2 - y1, B = x1 - x2, C = y1*x2 - x1*y2;
    return dist_dot_line(A, B, C, x, y);
}

// РАССТОЯНИЕ ОТ ТОЧКИ ДО ОТРЕЗКА
inline ld dist_dot_segment(ld x1, ld y1, ld x2, ld y2, ld x, ld y) {
    ld A = y2 - y1, B = x1 - x2, C = x2*y1 - x1*y2, xx1 = x1 + A, yy1 = y1 + B, xx2 = x2 + A,
    yy2 = y2 + B, A1 = yy1 - y1, B1 = x1 - xx1, C1 = xx1*y1 - yy1*x1,
    A2 = yy2 - y2, B2 = x2 - xx2, C2 = xx2*y2 - yy2*x2;
    ld z1 = A1*x + B1*y + C1, z2 = A2*x + B2*y + C2, ans;
    if (z1 * z2 > 0) ans = min(sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)),
                               sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2))); else
    ans = abs(A*x + B*y + C)/sqrt(A*A + B*B);
    return ans;
}

// ПЛОЩАДЬ ТРЕУГОЛЬНИКА
inline ld triangle_square (ld x1, ld y1, ld x2, ld y2, ld x3, ld y3) {
    return fabs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));
}

// ПЛОЩАДЬ ПРЯМОУГОЛЬНИКА
inline ld polygon_square (ld x [], ld y [], int n) {
    ld ans = 0;
    for (int i = 0; i < n; i++)
        ans += (y[i] + y[i + 1])*(x[i + 1] - x[i]);
    return abs(ans)/2;
}

// ВЫПУКЛЫЙ ИЛИ НЕТ
inline bool convex(ll x [], ll y [], int n) {
    x[n + 1] = x[1], y[n + 1] = y[1];
    x[n + 2] = x[2], y[n + 2] = y[2];
    x[0] = x[n], y[0] = y[n];
    for (int i = 1; i <= n; i++){
        ll x1 = x[i], x2 = x[i + 1], y1 = y[i], y2 = y[i + 1];
        ll z1 = (x2 - x1)*(y[i - 1] - y1) - (y2 - y1)*(x[i - 1] - x1);
        ll z2 = (x2 - x1)*(y[i + 2] - y1) - (y2 - y1)*(x[i + 2] - x1);
        if ((z1 > 0 && z2 < 0) || (z1 < 0 && z2 > 0)){
            return 0;
        }
    }
    return 1;
}

// ПЕРЕСЕКАЮТСЯ ЛИ ОТРЕЗКИ
inline bool bool_segments_intersection (ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) {
ll z3 = (x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1);
    ll z4 = (x4 - x1)*(y2 - y1) - (y4 - y1)*(x2 - x1);
    ll z1 = (x1 - x3)*(y4 - y3) - (y1 - y3)*(x4 - x3);
    ll z2 = (x2 - x3)*(y4 - y3) - (y2 - y3)*(x4 - x3);
    ll L = max(min(x1, x2), min(x3, x4)),
       R = min(max(x1, x2), max(x3, x4)),
       N = max(min(y1, y2), min(y3, y4)),
       W = min(max(y1, y2), min(y3, y4));
    if (L <= R && W >= N && !max(z1, z2) && !max(z3, z4)){
        return 1;
    }
    if (!max(z1, z2) && !max(z3, z4)){
        return 0;
    }
    if (z1*z2 > 0 || z3 * z4 > 0){
        return 0;
    } else {
        return 1;
    }
}


// ТОЧКА ПЕРЕСЕЧЕНИЯ ОТРЕЗКОВ
pair<ld, ld> segments_intersection(ll x1, ll y1,ll x2, ll y2, ll x3, ll y3, ll x4, ll y4){
    ll A1 = y2 - y1, B1 = x1 - x2, C1 = y1*x2 - y2*x1,
        A2 = y4 - y3, B2 = x3 - x4, C2 = y3*x4 - x3*y4;
    if (!bool_segments_intersection(x1, y1, x2, y2, x3, y3, x4, y4)) return {inf, inf};
    ld y = double(A1*C2 - A2*C1)/double(A2*B1 - A1*B2);
    ld x = double(B1*C2 - B2*C1)/double(B2*A1 - A2*B1);
    return {x, y};
}

// ТОЧКА ВНУТРИ МНОГОУГОЛЬНИКА ИЛИ НЕТ
inline bool in_polygon (ld x [], ld y [], int n, ld x0, ld y0)  {
    x[n] = x[0], y[n] = y[0];
    ld mn = x[0];
    for (int i = 0; i < n; i++) {
        mn = min(mn, x[i]);
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        ld z1 = (y[i] - y0) * (mn - x0);
        ld z2 = (y[i + 1] - y0) * (mn - x0);
        ld z3 = (x0 - x[i]) * (y[i + 1] - y[i]) - (y0 - y[i]) * (x[i + 1] - x[i]);
        ld z4 = (mn - x[i]) * (y[i + 1] - y[i]) - (y0 - y[i]) * (x[i + 1] - x[i]);
        if (z1 == 0 && z2 == 0) continue;
        if ((z2 == 0 && z1 > 0 && x0 > x[i + 1]) || (z1 == 0 && z2 > 0 && x0 > x[i])) k++;
        if (z1 * z2 < 0 && z3 * z4 < 0) k++;
    }
    return k%2;
}

// КОЛИЧЕСТВО ТОЧЕК НА ОТРЕЗКЕ
inline ll dots_on_segment (ll x1, ll y1, ll x2, ll y2) {
    return __gcd(abs(x1 - x2), abs(y1 - y2)) + 1;
}

// КОЛИЧЕСТВО ТОЧЕК В МНОГОУГОЛЬНИКЕ
inline int dots_in_polygon(ll x [], ll y [], int n) {
    ll Min = y[0];
    for (int i = 0; i < n; i++) {
        Min = min(Min, y[i]);
    }
    x[n] = x[0], y[n] = y[0];
    ll s = 0;
    ll kt = 0;
    for(int i = 0; i < n; i++) {
        s += (y[i] + y[i + 1]) * (x[i] - x[i + 1]);
        kt += __gcd(abs(x[i] - x[i + 1]), abs(y[i] - y[i + 1]));
    }
    s = abs(s);
    return (s - kt + 2) / 2;
}

// ПЕРЕСЕЧЕНИЕ ПРЯМЫХ
inline bool bool_line_intersection (ld x11, ld y11, ld x12, ld y12, ld x21, ld y21, ld x22, ld y22) {
    ld A1 = y12 - y11, B1 = x11 - x12, C1 = y11*x12 - x11*y12;
    ld A2 = y22 - y21, B2 = x21 - x22, C2 = y21*x22 - x21*y22;
    ld d = A1 * B2 - A2 * B1;
    return d != 0;
}

inline pair<ld, ld> line_intersection (ld x11, ld y11, ld x12, ld y12, ld x21, ld y21, ld x22, ld y22) {
    ld A1 = y12 - y11, B1 = x11 - x12, C1 = y11*x12 - x11*y12;
    ld A2 = y22 - y21, B2 = x21 - x22, C2 = y21*x22 - x21*y22;
    ld d = A1 * B2 - A2 * B1;
    if (d == 0) return {inf, inf};
    ld x = (B1 * C2 - B2 * C1) / d;
    ld y = (C1 * A2 - C2 * A1) / d;
    return {x, y};
}

// ВЫПУКЛАЯ ОБОЛОЧКА
ll mx, my;
inline bool comp(pair<int, int> a, pair<int, int> b)
{
    ll z = (a.F - mx) * (b.S - my) - (a.S - my) * (b.F - mx);
    ll d1 = (a.F - mx) * (a.F - mx) + (a.S - my) * (a.S - my);
    ll d2 = (b.F - mx) * (b.F - mx) + (b.S - my) * (b.S - my);
    return z > 0 || z == 0 && d1 < d2;
}

inline vector < int > convex_hull(vector < pair<int, int> > a, int n) {
    int p = 0;
    for(int i = 0; i < n; i++)
        if (a[i].S < a[p].S) p = i;
            else if (a[i].S == a[p].S && a[i].F < a[p].F) p = i;
    swap(a[0], a[p]);
    mx = a[0].F, my = a[0].S;
    sort(a.begin() + 1, a.end(), comp);
    vector<int> q;
    q.pb(0);
    q.pb(1);

    for(int i = 2; i < (int)a.size(); i++) {
        while((a[q[q.size() - 2]].F - a[q.back()].F) * (a[i].S - a[q.back()].S) -
              (a[q[q.size() - 2]].S - a[q.back()].S) * (a[i].F - a[q.back()].F) >= 0)
            {
                q.erase(q.end() - 1);
                if (q.size() == 1) break;
            }
        q.pb(i);
    }
    return q;
}

signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    IOS
    /*

    Ax + By + C = 0 ( -A / B = k , -C / b = l)
    y = kx + l;
    k = tg(alfa) - угол между осью O x и прямой
    A = y2 - y1, B = x1 - x2, C = x2*y1 - x1*y2
    */
}
