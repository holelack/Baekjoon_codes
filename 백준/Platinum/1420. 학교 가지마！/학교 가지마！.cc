#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>

using namespace std;
const int INF = 1e9;
int N, M;
int sink, source;
vector<string> city;

struct Edge {
    int u, ref, cap;
    Edge(int u, int cap, int ref) : u(u), cap(cap), ref(ref) {}
};

class Dinic {
    int V, S, T;
    vector<vector<Edge>> edges;
    vector<int> lv, nxt;
public:
    Dinic(int V, int S, int T) : V(V), S(S), T(T) {
        edges.resize(V);
        lv.resize(V);
        nxt.resize(V);
    }

    // ref 인덱스 설정을 안전하게 수정
    void addEdge(int v, int u, int cap) {
        edges[v].push_back(Edge(u, cap, (int)edges[u].size()));
        edges[u].push_back(Edge(v, 0, (int)edges[v].size() - 1));
    }

    bool bfs() {
        fill(lv.begin(), lv.end(), -1);
        deque<int> q = { S };
        lv[S] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop_front();
            for (auto& edge : edges[v]) {
                if (lv[edge.u] == -1 && edge.cap > 0) {
                    lv[edge.u] = lv[v] + 1;
                    q.push_back(edge.u);
                }
            }
        }
        return lv[T] != -1;
    }

    int dfs(int v, int mxflow) {
        if (v == T) return mxflow;
        for (int& i = nxt[v]; i < edges[v].size(); i++) {
            Edge& edge = edges[v][i];
            if (lv[v] + 1 == lv[edge.u] && edge.cap > 0) {
                int flow = dfs(edge.u, min(mxflow, edge.cap));
                if (flow > 0) {
                    edge.cap -= flow;
                    edges[edge.u][edge.ref].cap += flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int network_flow() {
        int res = 0;
        while (bfs()) {
            fill(nxt.begin(), nxt.end(), 0);
            while (int flow = dfs(S, INF)) {
                res += flow;
            }
        }
        return res;
    }
};

void solve() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (!(cin >> N >> M)) return;
    city.resize(N);
    int hX, hY, kX, kY;
    for (int i = 0; i < N; i++) {
        cin >> city[i];
        for (int j = 0; j < M; j++) {
            if (city[i][j] == 'H') { hX = i; hY = j; }
            if (city[i][j] == 'K') { kX = i; kY = j; }
        }
    }

    // 인접한 경우 즉시 종료
    if (abs(hX - kX) + abs(hY - kY) == 1) {
        cout << -1;
        return;
    }

    // 정점 분할: in(0 ~ NM-1), out(NM ~ 2NM-1)
    source = (hX * M + hY) + N * M; // H의 out
    sink = (kX * M + kY);          // K의 in
    Dinic network(2 * N * M, source, sink);

    int dy[] = { -1, 1, 0, 0 };
    int dx[] = { 0, 0, -1, 1 };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (city[i][j] == '#') continue;

            int curr = i * M + j;
            int inNode = curr;
            int outNode = curr + N * M;

            // 1. 자기 자신의 in -> out 연결 (칸 제거 비용)
            if (city[i][j] == 'H' || city[i][j] == 'K') {
                network.addEdge(inNode, outNode, INF);
            }
            else {
                network.addEdge(inNode, outNode, 1);
            }

            // 2. 다른 칸으로 이동 (out -> neighbor's in)
            for (int k = 0; k < 4; k++) {
                int ni = i + dy[k], nj = j + dx[k];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M && city[ni][nj] != '#') {
                    network.addEdge(outNode, ni * M + nj, INF);
                }
            }
        }
    }

    int ans = network.network_flow();
    cout << (ans >= INF ? -1 : ans);
}

int main() {
    solve();
    return 0;
}