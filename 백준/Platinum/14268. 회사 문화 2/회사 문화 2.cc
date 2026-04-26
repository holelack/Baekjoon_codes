#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> adj;
vector<long long> segtree, lazy;
vector<int> dfss, dfse;
int cnt = 0;

void dfs(int v, int p) {
    dfss[v] = ++cnt;
    for (int u : adj[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
    dfse[v] = cnt;
}

void prop(int s, int e, int node) {
    if (lazy[node] != 0) {
        segtree[node] += (long long)(e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int l, int r, int s, int e, int node, int val) {
    prop(s, e, node);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[node] += val;
        prop(s, e, node);
        return;
    }
    int mid = (s + e) >> 1;
    update(l, r, s, mid, node << 1, val);
    update(l, r, mid + 1, e, node << 1 | 1, val);
    segtree[node] = segtree[node << 1] + segtree[node << 1 | 1];
}

long long query(int l, int r, int s, int e, int node) {
    prop(s, e, node);
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return segtree[node];
    int mid = (s + e) >> 1;
    return query(l, r, s, mid, node << 1) + query(l, r, mid + 1, e, node << 1 | 1);
}

void init() {
    if (!(cin >> N >> M)) return;
    adj.assign(N + 1, vector<int>());
    segtree.assign(4 * N + 1, 0);
    lazy.assign(4 * N + 1, 0);
    dfss.resize(N + 1);
    dfse.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        int p;
        cin >> p;
        if (p == -1) continue;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    dfs(1, -1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init();
    int cmd, i, w;
    while (M--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> i >> w;
            update(dfss[i], dfse[i], 1, N, 1, w);
        } else {
            cin >> i;
            cout << query(dfss[i], dfss[i], 1, N, 1) << '\n';
        }
    }
    return 0;
}