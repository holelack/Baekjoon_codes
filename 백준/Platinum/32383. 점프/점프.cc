#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
#define sq(x) (x) * (x)
const int MAXN = 5e5 + 1, MOD = 1e9 + 7;
int N;
int P[MAXN], L[MAXN], R[MAXN];
ll A[MAXN];
ll sz[MAXN];
int root = 0;

void init() {
	fastio();
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> A[i];
	memset(sz, 0, sizeof(ll) * (N + 1));
	memset(P, 0, sizeof(int) * (N + 1));
	memset(L, 0, sizeof(int) * (N + 1));
	memset(R, 0, sizeof(int) * (N + 1));
}

void build() {
	stack<int> stk;
	int last;
	for (int i = 1; i <= N; i++) {
		last = 0;
		while (!stk.empty() && A[stk.top()] < A[i]) {
			last = stk.top();
			stk.pop();
		}
		if (!stk.empty()) {
			R[stk.top()] = i;
			P[i] = stk.top();
		}
		if (last) {
			L[i] = last;
			P[last] = i;
		}
		stk.push(i);
	}
	for (int i = 1; i <= N; i++) if (!P[i]) root = i;
}

int dfs(int u) {
	if (!L[u] && !R[u]) return sz[u] = 1;
	int ret = 0;
	if (L[u]) ret += dfs(L[u]);
	if (R[u]) ret += dfs(R[u]);
	return sz[u] = ret + 1;
}

void solve() {
	ll ans = 0;
	for (int i = 1; i <= N; i++) {
		if (i == root) continue;
		ll cost = sq(A[i] - A[P[i]]) % MOD;
		ll cnt = sz[i] * (N - sz[i]) % MOD;
		ans = (ans + cost * cnt) % MOD;
	}
	cout << ans;
}

int main() {
	init();
	build();
	dfs(root);
	solve();
	
	return 0;
}