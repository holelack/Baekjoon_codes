#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 9e18;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
int n;
vector<int> A, B;
struct line {
    ll a, b;
    ll eval(ll x) {
        return this->a * x + this->b;
    }
    line(ll a, ll b): a(a), b(b) {}
};

bool bad(const line& l1, const line& l2, const line& l3) {
    // l1.a * x + l1.b = l2.a * x + l2.b -> x = (l2.b - l1.b) / (l1.a-l2.a)
    // cx(l1, l2) >= cx(l2, l3) -> (l2.b - l1.b) * (l2.a - l3.a) >= (l3.b - l2.b) * (l1.a - l2.a)
    return (__int128)(l2.b - l1.b) * (l2.a - l3.a) >= (__int128)(l3.b - l2.b) * (l1.a - l2.a);
}

vector<line> hull;

void insert(line l) {
    hull.emplace_back(l);
    while (hull.size() >= 3 && bad(hull.end()[-3], hull.end()[-2], hull.end()[-1])) {
        hull.erase(hull.end()-2);
    }
}

ll query(ll x) {
    int l = 0, r = hull.size()-1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (hull[mid].eval(x) >= hull[mid+1].eval(x)) l = mid + 1;
        else r = mid;
    }
    return hull[l].eval(x);
}

void input() {
    fastio();
    cin >> n;
    A.assign(n, 0);
    B.assign(n, 0);
    for (int& a: A) cin >> a;
    for (int& b: B) cin >> b;
}

void solve() {
    input();
    vector<ll> dp(n, 0);
    
    insert(line(B[0], 0));
    for (int i = 1; i < n; i++) {
        dp[i] = query(A[i]);
        insert(line(B[i], dp[i]));
    }
    cout << dp[n-1];
}

int main() {
    solve();

    return 0;
}