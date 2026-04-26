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
vector<int> nElement;
int cnt[(int)1e6+1] = {0,};
int res = 0;
int s = 0, e = -1;

void add(int idx) {
    int& count = cnt[A[idx]];
    nElement[count]--;
    nElement[++count]++;
    res = max(res, count);
}

void sub(int idx) {
    int& count = cnt[A[idx]];
    nElement[count]--;
    nElement[--count]++;
    if (!nElement[res]) res--;
}

void input() {
    fastio();
    cin >> N;
    sq = sqrt(N);

    A.assign(N, 0);
    for (int& a: A) cin >> a;

    nElement.assign(N, 0);
    nElement[0] = N;
    
    cin >> M;
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