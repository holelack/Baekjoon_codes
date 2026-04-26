#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define hypot(a) (a.x) * (a.x) + (a.y) * (a.y)
#define ccw(a, b) (a.x) * (b.y) - (a.y) * (b.x)
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0);}

typedef struct point {
    ll x, y, i = 0;
    point(ll x, ll y, ll i = 0) : x(x), y(y), i(i) {}
    bool operator<(const point& other) const {
        return (this->y < other.y) || (this->y == other.y && this->x < other.x);
    }
    bool operator>(const point& other) const {
        return (this->y > other.y) || (this->y == other.y && this->x > other.x);
    }
    bool operator==(const point& other) const {
        return this->x == other.x && this->y == other.y;
    }
    point operator-(const point& other) const {
        return point(this->x - other.x, this->y - other.y);
    }
} point;

point base = point(0, 0);

bool cmp(const point& a, const point& b) {
    point A = a - base, B = b - base;
    if (A.y < 0 || (A.y == 0 && A.x < 0)) { 
        A.x = -A.x;
        A.y = -A.y; 
    }
    if (B.y < 0 || (B.y == 0 && B.x < 0)) {
        B.x = -B.x;
        B.y = -B.y;
    }
    if (ccw(A, B)) return ccw(A, B) > 0;
    return hypot(A) < hypot(B);
}

typedef struct Oil {
    ll lx, rx, y;
    Oil(ll lx, ll rx, ll y) : lx(lx), rx(rx), y(y) {}
    bool operator<(const Oil& other) const {
        return cmp(point(this->lx, this->y), point(other.lx, other.y));
    }
} Oil;

int n;
vector<Oil> deposits;
vector<point> P;

void input() {
    fastio();
    cin >> n;
    deposits.assign(n, Oil(0, 0, 0));
    for (auto& [lx, rx, y] : deposits) {
        cin >> lx >> rx >> y;
        if (lx > rx) swap(lx, rx);
    }
    for (int i = 0; i < n; i++) {
        P.emplace_back(point(deposits[i].lx, deposits[i].y, i << 1));
        P.emplace_back(point(deposits[i].rx, deposits[i].y, i << 1 | 1));
    }
}

void solve() {
    input();
    ll ans = 0;
    auto tmp = P;
    for (int i = 0; i < (n << 1); i++) {
        base = tmp[i];

        sort(P.begin(), P.end(), cmp);

        ll sum = deposits[i >> 1].rx - deposits[i >> 1].lx;
        vector<int> cnt(n, 0);
        ans = max(ans, sum);
        int minus = 0;
        point prev = base;
        for (int j = 0; j < P.size(); j++) {
            if (base.y == P[j].y) continue;
            int k = P[j].i >> 1;
            if (cnt[k] == 0) {
                sum += deposits[k].rx - deposits[k].lx;
                cnt[k]++;
                if (prev == base || ccw((prev-base),(P[j]-base))) {
                    sum -= minus;
                    minus = 0;
                }
                ans = max(ans, sum);
            }
            else if (cnt[k] == 1) {
                minus += deposits[k].rx - deposits[k].lx;
                cnt[k]++;
                continue;
            }
            else continue;
            ans = max(ans, sum);
            prev = P[j];
        }
    }
    cout << ans;
}

int main() {
    solve();

    return 0;
}