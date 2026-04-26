#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <math.h>
using namespace std;
const int INF = 1e9;
int N, M, K, L;
vector<vector<int>> adj;
vector<vector<int>> capacity;
vector<vector<int>> flow;
vector<int> visited;
deque<int> q;

int bfs(int source, int sink) {
    visited.assign(L, -1);
    visited[source] = source;
    q.clear();
    q.push_back(source);
    while (q.size()) {
        int v = q[0]; q.pop_front();
        for (int u: adj[v]) {
            if (visited[u] == -1 && capacity[v][u] - flow[v][u] > 0) {
                visited[u] = v;
                if (u == sink) return -1;
                q.push_back(u);
            }
        }
    }
    return 0;
}

int EdmondsKarp(int source, int sink) {
    int res = 0;
    while (bfs(source, sink)) {
        int aug = INF;
        for (int i = sink; i != source; i = visited[i])
            aug = min(aug, capacity[visited[i]][i] - flow[visited[i]][i]);
        
        for (int i = sink; i != source; i = visited[i]) {
            flow[visited[i]][i] += aug;
            flow[i][visited[i]] -= aug;
        }
        res += aug;
    }
    return res;
}

void addEdge(int u, int v, int val) {
    capacity[u][v] += val;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() {
    cin >> N >> M >> K;
    L = N+M+3; // 3: superSource, source, sink
    adj.assign(L, vector<int>());
    capacity.assign(L, vector<int>(L, 0));
    flow.assign(L, vector<int>(L,0));

    int n, work;
    for (int i = 2; i <= N+1; i++) {
        cin >> n;
        for (int j = 2; j <= n+1; j++) {
            cin >> work;
            addEdge(i, N+work+1, 1);
        }
    }
    for (int i = 2; i <= M+1; i++) {
        addEdge(N+i, L-1, 1);
    }

    int ans = 0;
    for (int i = 2; i <= N+1; i++) {
        addEdge(1, i, 1);
        ans += EdmondsKarp(1, L-1);
    }
    
    for (int i = 2; i <= N+1; i++) {
        addEdge(1, i, K);
    }
    addEdge(0, 1, K);
    ans += EdmondsKarp(0, L-1);
    
    cout << ans;    
    return 0;
}