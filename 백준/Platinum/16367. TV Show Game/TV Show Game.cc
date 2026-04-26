#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const int MAXN = 3e5 + 3;
stack<int> stk;
bool onStack[MAXN];
int disc[MAXN], low[MAXN], SCC[MAXN];
int dfsn = 0, sccn = 0;
vector<int> adj[MAXN];

int k, n;

void addClause(int node1, int node2) {
	adj[node1^1].push_back(node2);
	adj[node2^1].push_back(node1);
}

void tarjan(int u) {
	disc[u] = low[u] = ++dfsn;
	stk.push(u);
	onStack[u] = true;
	for (int v : adj[u]) {
		if (!disc[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (onStack[v]) {
			low[u] = min(low[u], disc[v]);
		}
	}
	if (low[u] == disc[u]) {
		sccn++;
		while (!stk.empty()) {
			int v = stk.top(); stk.pop();
			onStack[v] = false;
			SCC[v] = sccn;
			if (u == v) break;
		}
	}
}

void init() {
	fastio();
	cin >> k >> n;
	int l1, l2, l3;
	char c1, c2, c3;
	for (int i = 0; i < n; i++) {
		cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;
		l1--; l2--; l3--;
		l1 <<= 1; l2 <<= 1; l3 <<= 1;
		
		if (c1 == 'B') l1 ^= 1;
		if (c2 == 'B') l2 ^= 1;
		if (c3 == 'B') l3 ^= 1;
		addClause(l1, l2);
		addClause(l2, l3);
		addClause(l1, l3);
	}
	memset(onStack, false, sizeof(onStack));
	memset(disc, 0, sizeof(disc));
	memset(low, 0, sizeof(low));
	memset(SCC, 0, sizeof(SCC));
}

void solve() {
	for (int u = 0; u < 2 * k; u++) {
		if (!disc[u]) tarjan(u);
	}
	vector<char> ans;
	for (int u = 0; u < 2 * k; u += 2) {
		if (SCC[u] == SCC[u ^ 1]) {
			cout << -1;
			return;
		}
		else if (SCC[u] < SCC[u ^ 1]) {
			ans.push_back('R');
		}
		else ans.push_back('B');
	}
	for (char c : ans) cout << c;
}

int main() {
	init();
	solve();

	return 0;
}