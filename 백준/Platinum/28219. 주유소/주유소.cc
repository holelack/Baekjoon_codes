#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const int MAXN = 2e5 + 1;
int N, K;
vector<int> adj[MAXN];
int dp[MAXN]; // dp[u] = no gas station count

void init() {
	fastio();
	cin >> N >> K;
	int u, v;
	for (int i = 1; i < N; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

int dfs(int u, int p) {
	int mx1 = 0, mx2 = 0;
	if (p != 0 && adj[u].size() == 1) {
		dp[u] = 1;
		return 0;
	}

	int sum = 0;
	for (int v : adj[u]) {
		if (v == p) continue;
		sum += dfs(v, u);
		int nval = dp[v];
		if (mx1 <= nval) {
			mx2 = mx1;
			mx1 = nval;
		}
		else if (mx2 < nval) mx2 = nval;
	}
	
	if (mx1 + mx2 >= K) {
		dp[u] = 0;
		return sum + 1;
	}
	else {
		dp[u] = mx1 + 1;
		return sum;
	}
}

int main() {
	init();
	cout << dfs(1, 0);

	return 0;
}