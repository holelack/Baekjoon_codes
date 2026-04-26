#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> point;
typedef struct Star {
    ll x, y;
    ll dx, dy;
} Star;
int N, T;
vector<Star> star;

ll dist(point P1, point P2) {
    ll dx = P1.first - P2.first;
    ll dy = P1.second - P2.second;
    return dx * dx + dy * dy;
}

ll CCW(point P1, point P2, point P3) {
    return (P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first);
}

vector<point> hull;
void getHull(int t) {
    vector<point> curr(N);
    for(int i=0; i<N; i++) {
        curr[i] = {star[i].x + star[i].dx * t, star[i].y + star[i].dy * t};
    }
    sort(curr.begin(), curr.end());

    vector<point> lower, upper;
    for (int i = 0; i < N; i++) {
        while (lower.size() >= 2 && CCW(lower[lower.size()-2], lower.back(), curr[i]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(curr[i]);
    }
    lower.pop_back();
    for (int i = N-1; i >= 0; i--) {
        while (upper.size() >= 2 && CCW(upper[upper.size()-2], upper.back(), curr[i]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(curr[i]);
    }
    upper.pop_back();
    hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());
}

ll diameter(int t) {
    getHull(t);
    int L = hull.size();
    if (L <= 1) return 0;
    if (L == 2) return dist(hull[0], hull[1]);
    int i = 0, j = 1;
    ll ret = 0;
    while (i < L) {
        point a = hull[i], b = hull[(i+1) % L], c = hull[j], d = hull[(j+1)%L];
        ret = max(ret, dist(a, c));
        d.first -= c.first - b.first;
        d.second -= c.second - b.second;
        if (CCW(a, b, d) > 0) j = (j+1) % L;
        else ++i;
    }
    return ret;
}

void ternary_search() {
    int l = 0, r = T;
    while (r - l >= 3) {
        int p = (l*2 + r) / 3, q = (l + r*2) / 3;
        if (diameter(p) <= diameter(q)) r = q;
        else l = p;
    }
    int mnt = l;
    ll mnd = diameter(l);
    for (int t = l+1; t <= r; t++) {
        ll d = diameter(t);
        if (d < mnd) {
            mnt = t;
            mnd = d;
        }
    }
    cout << mnt << '\n' << mnd;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> T;
    star.resize(N);
    for (auto& [x,y,dx,dy]: star) cin >> x >> y >> dx >> dy;
    ternary_search();
    return 0;
}