#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const int MAXN = 3e5 + 1;
int T;
int N;
int A[MAXN], perm[MAXN];
vector<int> invA[MAXN];
int BIT[MAXN << 2];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> A[i];
	for (int i = 1; i <= N; i++) invA[i].clear();
	for (int i = 1; i <= N; i++) invA[A[i]].push_back(i);
}

void update(int i, int v) {
	for (int bit = i; bit <= N; bit += bit & -bit) {
		BIT[bit] += v;
	}
}

int query(int i) {
	int res = 0;
	for (int bit = i; bit > 0; bit -= bit & -bit) {
		res += BIT[bit];
	}
	return res;
}

int main() {
	fastio();
	cin >> T;
	while (T--) {
		init();
		
		priority_queue<int> pq;

		bool flag = false;
		for (int i = N; i > 0; i--) {
			for (int j : invA[i]) pq.push(j);
			if (pq.empty()) {
				flag = true;
				break;
			}
			perm[i] = pq.top(); pq.pop();
		}
		if (flag) {
			cout << "-1\n";
			continue;
		}

		ll inversion = 0;
		memset(BIT, 0, sizeof(int) * (N + 2));
		for (int i = N; i > 0; i--) {
			inversion += query(perm[i]);
			update(perm[i], 1);
		}
		cout << inversion << "\n";
	}

	return 0;
}