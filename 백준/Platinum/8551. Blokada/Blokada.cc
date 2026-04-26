#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int N,M;
typedef struct edge {
    int to, rev, cap;
} edge;

vector<vector<edge>> adj;
vector<int> level;
vector<int> ptr;

void addEdge(int u, int v, int c) {
    adj[u].emplace_back((edge){v, (int)adj[v].size(), c});
    adj[v].emplace_back((edge){u, (int)adj[u].size() - 1, 0});
}

int bfs(int source, int sink) {
    level.assign(N, INF);
    deque<int> q;
    q.emplace_back(source);
    level[source] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        for (auto &e: adj[u]) {
            if (level[e.to] == INF && e.cap > 0) {
                level[e.to] = level[u] + 1;
                q.emplace_back(e.to);
            }
        }
    }
    return level[sink] != INF;
}

int dfs(int source, int sink, int u, int max_flow) {
    if (u == sink) return max_flow;
    for (int& i = ptr[u]; i < adj[u].size(); i++) {
        edge &e = adj[u][i];
        if (e.cap > 0 && level[e.to] == level[u] + 1) {
            int f = dfs(source, sink, e.to, min(max_flow, e.cap));
            if (f>0) {
                e.cap -= f;
                adj[e.to][e.rev].cap += f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(int source, int sink) {
    int res = 0;
    while (bfs(source, sink)) {
        fill(ptr.begin(), ptr.end(), 0);
        while (true) {
            int f = dfs(source, sink, source, INF);
            if (!f) break;
            res += f;
        }
    }
    return res;
}

int main() {
    cin >> N >> M;
    adj.assign(N,{});
    level.assign(N, INF);
    ptr.assign(N,0);
    
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        addEdge(--a,--b,1);
    }
    
    cout << dinic(0, N-1);
    return 0;
}