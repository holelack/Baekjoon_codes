#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[(int)1e5+1][20];
vector<int> adj[(int)1e5+1];
vector<int> child[(int)1e5+1];
int n;

void dfs(int now, int prv) {
	for (auto nxt : adj[now]) {
		if (nxt != prv) {
			child[now].push_back(nxt);
			dfs(nxt, now);
		}
	}
}

ll solve(int now, int color) {
	ll& res = dp[now][color];
	if (res != -1) return res;

	ll prv = 0;

	for (auto nxt : child[now]) {
		ll tmp = 1e16;
		for (int i = 1; i < 20; i++) {
			if (color == i) continue;
			tmp = min(tmp, solve(nxt, i));
		}
		prv += tmp;
	}
	return res = prv + color;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1, 1);
	memset(dp, -1, sizeof(dp));

	ll ans = 1e16;
	for (int i = 1; i < 20; i++) {
		ans = min(ans, solve(1, i));
	}

	cout << ans;
}