#include <bits/stdc++.h>
using namespace std;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
int n, s;
vector<vector<int>> adj;
vector<int> parent;
map<vector<int>, int> iso;
int treeID = 0;

void input() {
    cin >> s;
    adj.assign(s, {});
    int u, v;
    for (int i = 1; i < s; i++) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
}

int getID(int u, int p) {
    vector<int> canon;
    for (int v: adj[u]) {
        if (v == p) continue;
        canon.push_back(getID(v, u));
    }
    sort(canon.begin(), canon.end());

    if (iso.find(canon) == iso.end()) {
        iso[canon] = ++treeID;
    }
    return iso[canon];
}

int farthest(int root) {
    parent.assign(s, -1);
    queue<int> q;
    q.push(root);
    int far = root;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        far = u;
        for (int v: adj[u]) {
            if (v == parent[u]) continue;
            q.push(v);
            parent[v] = u;
        }
    }
    return far;
}

pair<int,int> centers() {
    int l = farthest(0);
    int r = farthest(l);
    vector<int> path;
    for (int u = r; u != -1; u = parent[u]) {
        path.emplace_back(u);
    }
    if (path.size() & 1) return make_pair(path[path.size()>>1], -1);
    return make_pair(path[path.size()>>1], path[(path.size()>>1)-1]);
    return make_pair(-1,-1);
}

void solve() {
    fastio();
    cin >> n;
    vector<int> constellation(n, 0);
    for (int i = 0; i < n; i++) {
        input();
        auto [cent1, cent2] = centers();
        int id1, id2;
        id1 = getID(cent1, -1);
        if (cent2 == -1) id2 = id1;
        else id2 = getID(cent2, -1);
        constellation[i] = min(id1, id2);
    }
    sort(constellation.begin(), constellation.end());
    constellation.erase(unique(constellation.begin(), constellation.end()), constellation.end());

    cout << constellation.size();
}

int main() {
    solve();

    return 0;
}