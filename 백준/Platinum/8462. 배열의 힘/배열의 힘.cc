#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int N, M, sq;
typedef struct Query {
    int i;
    int l, r;
    bool operator<(const Query& other) const {
        if (this->l/sq != other.l/sq) return this->l/sq < other.l/sq;
        return this->r < other.r; 
    }
} Query;
vector<Query> Q;
vector<int> A;
vector<ll> ans;
ll cnt[(int)1e6+1] = {0,};
ll res = 0;
int s = 0, e = -1;

void add(int idx) {
    ll& Ks = cnt[A[idx]];
    res += ((Ks+1)*(Ks+1) - Ks*Ks) * A[idx];
    Ks++;
}

void sub(int idx) {
    ll& Ks = cnt[A[idx]];
    res += ((Ks-1)*(Ks-1) - Ks*Ks) * A[idx];
    Ks--;
}

void input() {
    fastio();
    cin >> N >> M;
    A.assign(N, 0);
    for (int& a: A) cin >> a;
    sq = sqrt(N);
    Q.assign(M, Query());
    for (int i = 0; i < M; i++) {
        Q[i].i = i;
        cin >> Q[i].l >> Q[i].r;
        Q[i].l--; Q[i].r--;
    }
    sort(Q.begin(), Q.end());
    ans.assign(M, 0);
}

void solve() {
    input();
    for (int i = 0; i < M; i++) {
        while (s < Q[i].l) sub(s++);
        while (s > Q[i].l) add(--s);
        while (e < Q[i].r) add(++e);
        while (e > Q[i].r) sub(e--);
        ans[Q[i].i] = res;
    }
    for (ll i: ans) cout << i << '\n';
}

int main() {
    solve();

    return 0;
}