#include <iostream>
#include <vector>
#include <math.h>
#include <deque>
#include <algorithm>
using namespace std;

const int INF = 1e9;
int N, K, H, M, L;
vector<vector<int>> capacity;
vector<vector<int>> flow;
vector<vector<int>> adj;
vector<int> visited;
deque<int> q;


long long CCW(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
    return ((long long)B.first - A.first) * (C.second - A.second) - ((long long)B.second - A.second) * (C.first - A.first);
}

// if CCW(P1,P2,P3) or order is (P1 - P2 - P3)(collinear) 
bool inSquare(pair<int, int> P1, pair<int,int> P2, pair<int,int> P3) {
    if (CCW(P1,P2,P3)) return false;
    int minX, maxX, minY, maxY;
    minX = min(P1.first, P2.first); maxX = max(P1.first, P2.first);
    minY = min(P1.second, P2.second); maxY = max(P1.second, P2.second);
    if (minX < P3.first && P3.first < maxX || minY < P3.second && P3.second < maxY) {
        return true;
    }
    return false;
}

// strict intersect + inSquare() if P1,P2,P3 are collinear.
bool intersect(pair<int,int> P1, pair<int,int> P2, pair<int,int> P3, pair<int,int> P4) {
    long long c1 = CCW(P1,P2,P3), c2 = CCW(P1,P2,P4), c3 = CCW(P3,P4,P1), c4 = CCW(P3,P4,P2);

    bool flag1 = (c1 < 0 && c2 > 0), flag2 = (c1 > 0 && c2 < 0);
    bool flag3 = (c3 < 0 && c4 > 0), flag4 = (c3 > 0 && c4 < 0);

    // use this form to avoid overflow.
    if ((flag1 || flag2) && (flag3 || flag4)) return true;
    else if (inSquare(P1,P2,P3)) return true;
    else return false;
}

// network_flow
int bfs(int source, int sink) {
    visited.assign(L, -1);
    visited[source] = source;
    q.clear();
    q.push_back(source);
    while (q.size()) {
        int v = q.front(); q.pop_front();
        for (int u: adj[v]) {
            if (visited[u] == -1 && capacity[v][u] - flow[v][u]) {
                visited[u] = v;
                if (u == sink) return 1;
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

void addEdge(int v, int u, int val) {
    capacity[v][u] += val;
    adj[v].push_back(u);
    adj[u].push_back(v);
}

int main() {
    cin >> N >> K >> H >> M;
    L = M+H+2; // total nodes of network flow algorithm
    vector<pair<int,int>> P;
    //input
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        P.push_back({x, y});
    }
    vector<pair<int,int>> holes;
    for (int i = 0; i < H; i++) {
        int x, y;
        cin >> x >> y;
        holes.push_back({x,y});
    }
    vector<pair<int,int>> mice;
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        mice.push_back({x,y});
    }
    capacity.assign(L, vector<int>(L, 0));
    flow.assign(L, vector<int>(L, 0));
    adj.assign(L, vector<int>());

    // making graph
    for (int i = 0; i < M; i++) { // mice -> holes
        for (int j = 0; j < H; j++) {
            bool flag = true;
            for (int k = 0; k < N; k++) {
                if (intersect(mice[i], holes[j], P[k], P[(k+1)%N]))
                    flag = false;
            }
            if (flag) addEdge(i + 1, M + j + 1, 1);
        }
    }
    
    for (int i = 1; i <= M; i++) { // source -> mice
        addEdge(0, i, 1);
    }
    for (int i = 1; i <= H; i++) { // holes -> sink
        addEdge(M+i, L-1, K);
    }
    
    int temp = EdmondsKarp(0, L-1);
    if (temp < M) cout << "Impossible";
    else cout << "Possible";

    return 0;
}