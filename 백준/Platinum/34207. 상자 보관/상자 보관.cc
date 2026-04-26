#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int N, L;
vector<pair<int, int>> box;
vector<int> tree, lazy; // update: assign, query: max

void prop(int s, int e, int node) {
	if (!lazy[node]) return;
	tree[node] += lazy[node];
	if (s != e) {
		lazy[node << 1] += lazy[node];
		lazy[node << 1 | 1] += lazy[node];
	}
	lazy[node] = 0;
}

void update(int s, int e, int l, int r, int val, int node) {
	prop(s, e, node);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		lazy[node] = val;
		prop(s, e, node);
		return;
	}
	int mid = (s + e) >> 1;
	update(s, mid, l, r, val, node << 1);
	update(mid + 1, e, l, r, val, node << 1 | 1);
	// query: max
	tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
}

int query(int s, int e, int l, int r, int node) {
	prop(s, e, node);
	if (e < l || r < s) return 0;
	if (l <= s && e <= r) return tree[node];
	int mid = (s + e) >> 1;
	return max(query(s, mid, l, r, node << 1), query(mid + 1, e, l, r, node << 1 | 1));
}

int compress(vector<pair<int, int>>& v) {
	vector<int> tmp;
	for (auto i : v) {
		tmp.emplace_back(i.first);
		tmp.emplace_back(i.second);
	}
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	for (auto& i : v) {
		i.first = lower_bound(tmp.begin(), tmp.end(), i.first) - tmp.begin();
		i.second = lower_bound(tmp.begin(), tmp.end(), i.second) - tmp.begin();
	}
	return tmp.size();
}

void input() {
	fastio();
	cin >> N;
	box.assign(N, pair<int, int>());
	for (auto& i : box) cin >> i.first >> i.second;
	L = compress(box);
	tree.assign(L << 2, 0);
	lazy.assign(L << 2, 0);
}

int main() {
	input();
	for (auto i: box) {
		update(0, L-1, i.second, i.first-1, 1, 1);
		cout << query(0, L - 1, 0, L - 1, 1) << '\n';
	}

	return 0;
}