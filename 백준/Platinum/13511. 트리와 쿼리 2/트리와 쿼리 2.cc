#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
 
#define MAX 18
int n, u, v, w, m;
vector <pair<int,int>> adj[100010];
int depth[100010];
int parent[100010][MAX];
long long cost[100010];
 
void dfs(int node) {
    for (int i = 0; i < adj[node].size(); i++) {
        int next = adj[node][i].first;
        if (depth[next] == -1) {
            parent[next][0] = node;
            depth[next] = depth[node] + 1;
            cost[next] += adj[node][i].second + cost[node];
            dfs(next);
        }
    }
}
int main() {
 
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back({ v,w });
        adj[v].push_back({ u,w });
    }
    scanf("%d", &m);
    memset(depth, -1, sizeof(depth));
    memset(parent, -1, sizeof(parent));
    
    depth[1] = 0;
    dfs(1);
 
    for (int k = 0; k < MAX - 1; k++) {
        for (int i = 2; i <= n; i++) {
            parent[i][k + 1] = parent[parent[i][k]][k];
        }
    }
 
    int num, k;
    while (m--)
    {
        scanf("%d %d %d", &num, &u, &v);
        if (num == 1) {
            
            long long Temp_c = cost[u] + cost[v];
 
            if (depth[u] < depth[v]) swap(u, v);
            for (int i = MAX - 1; i >= 0; i--) {
                if (depth[u] - depth[v] >= 1 << i) {
                    u = parent[u][i];
                }
            }
            if (u != v) {
                for (int i = MAX - 1; i >= 0; i--) {
                    if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
                        u = parent[u][i];
                        v = parent[v][i];
                    }
                }
                u = parent[u][0];
            }

            Temp_c -= 2 * cost[u];
            printf("%lld\n", Temp_c);
 
        }
        else {
            scanf("%d", &k);
 
            int Temp_u = u;
            int Temp_v = v;
            
            if (depth[u] < depth[v]) swap(u, v); 
 
            for (int i = MAX - 1; i >= 0; i--) {
                if (depth[u] - depth[v] >= 1 << i) {
                    u = parent[u][i];
                }
            }
            if (u != v) {
                for (int i = MAX - 1; i >= 0; i--) {
                    if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
                        u = parent[u][i];
                        v = parent[v][i];
                    }
                }
                u = parent[u][0];
            }
            
            int cnt = depth[Temp_u] - depth[u] + 1;
 
            if (k == cnt) {
                printf("%d\n", u);
            }
            else if (k < cnt) {
                k--;
                for (int i = MAX-1; k; i--) {
                    if (k & 1 << i) {
                        Temp_u = parent[Temp_u][i];
                        k -= 1 << i;
                    }
                    
                }
                printf("%d\n", Temp_u);
            }
            else {
                k -= cnt;
                k = depth[Temp_v]-depth[u]-k;
                for (int i = MAX - 1; k; i--) {
                    if (k & 1 << i) {
                        Temp_v = parent[Temp_v][i];
                        k -= 1 << i;
                    }
                    
                }
                printf("%d\n", Temp_v);
            }
 
 
        }
    }
    return 0;
}
