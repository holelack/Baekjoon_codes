#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const ll INF = 1e18;
const ll MAXN = 2e5 + 1;
ll N;
ll dp[MAXN], weak[MAXN]; // dp[u] = 정점 u부터 시작했을 때 최소 전력량
vector<ll> G[MAXN], invG[MAXN], dp2[MAXN]; // dp2[u][v] = previous dp value of u -> v
ll U[MAXN], Z[MAXN], R[MAXN], cnt[MAXN];
priority_queue<pair<ll, ll>> pq;


void init() {
	fastio();
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> U[i] >> Z[i] >> R[i];
		G[i].assign(R[i], 0);
		for (ll& g : G[i]) cin >> g;
		for (ll g : G[i]) invG[g].push_back(i);
	}

	fill(dp, dp + (N + 1), INF);
	for (int i = 1; i <= N; i++) {
		dp2[i].assign(invG[i].size(), 0);
	}
	memset(cnt, 0, sizeof(ll) * (N + 1));

	for (int i = 1; i <= N; i++) {
		dp[i] = Z[i];
		weak[i] = 0;
		pq.push(make_pair(-dp[i], i));
	}
}

int main() {
	init();

	while (!pq.empty()) {
		auto [dist, u] = pq.top(); pq.pop();
		dist = -dist; // minpq

		if (dist > dp[u]) continue;
		for (int i = 0; i < invG[u].size(); i++) {
			int v = invG[u][i];
			cnt[v]++;
			weak[v] -= dp2[u][i] - dp[u]; // decrement by difference with previous value
			dp2[u][i] = dp[u];

			if (cnt[v] == R[v]) weak[v] += U[v];
			if (cnt[v] >= R[v] && weak[v] < dp[v]) {
				dp[v] = weak[v];
				pq.push(make_pair(-dp[v], v));
			}
		}
	}
	cout << dp[1];

	return 0;
}