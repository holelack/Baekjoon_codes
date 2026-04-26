#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int N, M;
vector<int> parent;
vector<vector<int>> child;
vector<pair<int,int>> Q;
vector<pair<int,int>> interval;
vector<int> tree, lazy;
int dfsn = -1;

void input() {
    fastio();
    cin >> N;
    parent.assign(N, 0);
    child.assign(N, {});
    for (int& p: parent) {
        cin >> p;
        p--;
    }
    for (int i = 1; i < N; i++) {
        child[parent[i]].emplace_back(i);
    }
    cin >> M;
    Q.assign(M, pair<int,int>());
    for (auto& [cmd, i]: Q) cin >> cmd >> i;
    interval.assign(N, pair<int,int>());
    tree.assign(4*N, 0);
    lazy.assign(4*N, -1);
}

void dfs(int u) {
    interval[u].first = ++dfsn;
    for (int v: child[u]) dfs(v);
    interval[u].second = dfsn;
}

void prop(int s, int e, int node) {
    if (lazy[node]==-1) return;
    tree[node] = (e-s+1) * lazy[node];
    if (s!=e) lazy[node<<1] = lazy[node<<1|1] = lazy[node];
    lazy[node] = -1;
}

void update(int s, int e, int l, int r, int val, int node) {
    if (l > r) return;
    prop(s,e,node);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[node] = val;
        prop(s, e, node);
        return;
    }
    int mid = (s + e) >> 1;
    update(s, mid, l, r, val, node<<1);
    update(mid+1, e, l, r, val, node<<1|1);
    tree[node] = tree[node<<1] + tree[node<<1|1];
}

int query(int s, int e, int l, int r, int node) {
    if (l > r) return 0;
    prop(s, e, node);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[node];
    int mid = (s + e) >> 1;
    return query(s, mid, l, r, node<<1) + query(mid+1, e, l, r, node<<1|1);
}

void solve() {
    input();
    dfs(0);
    
    update(0, N-1, 0, N-1, 1, 1);
    for (auto [cmd, i]: Q) {
        i--;
        if (cmd == 1) update(0, N-1, interval[i].first+1, interval[i].second, 1, 1);
        if (cmd == 2) update(0, N-1, interval[i].first+1, interval[i].second, 0, 1);
        if (cmd == 3) cout << query(0, N-1, interval[i].first+1, interval[i].second, 1) << '\n';
    }
}

int main() {
    solve();

    return 0;
}

