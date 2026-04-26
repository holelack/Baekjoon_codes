#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <deque>
using namespace std;
const int INF = 1e9;
int N, M, s, p, S, P;
int L;
vector<int> money;
vector<vector<int>> graph;
vector<bool> isCross;

vector<int> value;
vector<vector<int>> dag;

vector<vector<int>> SCC;
vector<int> low;
vector<int> disc;
vector<int> stack;
vector<int> visited;
vector<int> visit;
vector<int> isRestuarant;
vector<int> isSCCRest;

vector<int> topo; // begining with S

vector<int> dp;

int cnt = 0;

void getSCC(int cur) {
    visited[cur] = 1;
    visit[cur] = 1;
    stack.emplace_back(cur);
    disc[cur] = ++cnt;
    low[cur] = cnt;
    
    for (int nxt: graph[cur]) {
        if (!disc[nxt]) {
            getSCC(nxt);
            low[cur] = min(low[cur], low[nxt]);
        } else if(visited[nxt]) {
            low[cur] = min(low[cur], disc[nxt]);
        }
    }
    
    if (low[cur] == disc[cur]) {
        vector<int> temp;
        while (!stack.empty()) {
            int popped = stack[stack.size()-1]; stack.pop_back();
            temp.emplace_back(popped);
            visited[popped] = 0;
            if (cur == popped) break;
        }
        SCC.emplace_back(temp);
    }
}

int dfs(int u) {
    if (dp[u]) return dp[u];
    int _max = 0;
    for (int v: dag[u])
        _max = max(_max, dfs(v));
    if (!_max) {
        if (isSCCRest[u]) return value[u];
        else return 0;
    }
    else dp[u] = _max + value[u];
    return dp[u];
}

int main() {
    cin >> N >> M;
    money.resize(N);
    stack = vector<int>();
    graph.assign(N, vector<int>());
    for (int i = 0; i < M; i++) {
        cin >> s >> p;
        graph[--s].emplace_back(--p);
    }
    for (int i = 0; i < N; i++) 
        cin >> money[i];
    cin >> S >> P; --S;
    isRestuarant.assign(N,0);
    int restaurant;
    for (int i = 0; i < P; i++) {
        cin >> restaurant;
        isRestuarant[--restaurant] = 1;
    }
    
    int idx;
    
    low.resize(N);
    disc.assign(N,0);
    visited.assign(N, 0);
    visit.assign(N,0);
    for (int i = 0; i < N; i++)
        if (!visit[i]) getSCC(i);
    L = SCC.size();
    
    isSCCRest.assign(L,0);
    for (int i = 0; i < L; i++) {
        for (int j: SCC[i]) {
            if (isRestuarant[j]) {
                isSCCRest[i] = 1;
                break;
            }
        }
    }
    
    vector<int> reverse(N);
    value.assign(L,0);
    for (int i = 0; i < L; i++) {
        for (int j: SCC[i]) {
            reverse[j] = i;
            value[i] += money[j];
        }
    }
    vector<pair<int,int>> edges;
    for (int i = 0; i < N; i++) {
        for (int j: graph[i]) {
            edges.emplace_back(pair<int,int>(reverse[i], reverse[j]));
        }
    }
        
    sort(edges.begin(), edges.end());
    edges.erase(unique(edges.begin(), edges.end()), edges.end());
    
    dag.assign(L, {});
    for (auto [s, e]: edges) {
        if (s==e) continue;
        dag[s].emplace_back(e);
    }

    dp.assign(L, 0);
    cout << dfs(reverse[S]);
    
    return 0;
}