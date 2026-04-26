#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using Point = pair<int,int>;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int N;
typedef struct Stick {
    int x1,y1,x2,y2;
} Stick;
vector<Stick> stick;
vector<vector<int>> adj, sccs;
vector<int> num, low, visited, stk;
int dfsn = 0;

int scc(int v) {
    num[v] = low[v] = ++dfsn;
    visited[v] = 1;
    stk.emplace_back(v);
    for (int nv: adj[v]) {
        if (!num[nv]) low[v] = min(low[v], scc(nv));
        else if (visited[nv]) low[v] = min(low[v], num[nv]);
    }
    if (low[v] == num[v]) {
        sccs.emplace_back();
        while (1) {
            int node = stk.back(); stk.pop_back();
            sccs.back().emplace_back(node);
            visited[node] = 0;
            if (node == v) break;
        }
    }
    return low[v];
}

int ccw(Point P1, Point P2, Point P3) {
    ll product = (P2.first - P1.first) * (P3.second - P1.second) - (P2.second - P1.second) * (P3.first - P1.first);
    if (product < 0) return -1;
    else if (product > 0) return 1;
    else return 0;
}

bool intersect(Stick s1, Stick s2) {
    Point P1 = Point(s1.x1, s1.y1);
    Point P2 = Point(s1.x2, s1.y2);
    Point P3 = Point(s2.x1, s2.y1);
    Point P4 = Point(s2.x2, s2.y2);
    int flag1 = ccw(P1,P2,P3) * ccw(P1,P2,P4);
    int flag2 = ccw(P3,P4,P1) * ccw(P3,P4,P2);
    if (flag1 == 0 && flag2 == 0) {
        if (P1 > P2) swap(P1,P2);
        if (P3 > P4) swap(P3,P4);
        return P3 <= P2 && P1 <= P4;
    }
    return flag1 <= 0 && flag2 <= 0;
}

void addEdge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v^1].emplace_back(u^1);
}

void input() {
    fastio();
    cin >> N;
    stick.assign(3*N, Stick());
    for (auto& [x1,y1,x2,y2]: stick) {
        cin >> x1 >> y1 >> x2 >> y2;
    }
    adj.assign(6*N, {});
    for (int i = 0; i < N; i++) {
        int a = (3 * i) << 1;
        int b = (3 * i + 1) << 1;
        int c = (3 * i + 2) << 1;
        addEdge(a | 1, b); addEdge(a | 1, c);
        addEdge(b | 1, a); addEdge(b | 1, c);
        addEdge(c | 1, a); addEdge(c | 1, b);
    }
    for (int i = 0; i < 3*N; i++) {
        for (int j = i+1; j < 3*N; j++) {
            if (intersect(stick[i], stick[j])) {
                addEdge(i<<1, j<<1|1);
            }
        }
    }

    num.assign(6*N, 0);
    low.assign(6*N, 0);
    visited.assign(6*N, 0);
}

int main() {
    input();
    for (int i = 0; i < 6*N; i++) {
        if (!num[i]) scc(i);
    }
    int M = sccs.size();
    vector<int> sccid(6*N, 0);
    for (int i = 0; i < M; i++) {
        for (int j: sccs[i]) {
            sccid[j] = i;
        }
    }
    vector<int> ans;
    for (int i = 0; i < 3*N; i++) {
        if (sccid[i<<1] == sccid[i<<1|1]) {
            cout << -1;
            return 0;
        }
        if (sccid[i<<1] > sccid[i<<1|1]) ans.emplace_back(i+1);
    }
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << " ";

    return 0;
}