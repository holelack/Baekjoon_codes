#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const int MOD = 1e9 + 7;
int N, M;
int S, T;

struct Edge {
	int u, v, i;
	Edge(int u, int v, int i) : u(u), v(v), i(i) {}
};

vector<Edge> edges;
int parent[2001];
int power3[2001];

void init() {
	fastio();
	cin >> N >> M;

	int a, b;
	power3[0] = 1;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		edges.push_back(Edge(a, b, i));
		power3[i + 1] = (ll)power3[i] * 3 % MOD;
	}

	S = 0;
	T = N - 1;

	iota(parent, parent + N, 0);
}

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (a != b) parent[a] = b;
}

int main() {
	init();

	int res = 0;
	while (!edges.empty()) {
		auto [u, v, i] = edges.back(); edges.pop_back();

		S = find(S); T = find(T);
		if (find(u) == S && find(v) == T || find(u) == T && find(v) == S) res = (res + power3[i]) % MOD;
		else unite(u, v);
	}
	cout << res;

	return 0;
}