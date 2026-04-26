#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}

const int MAXN = 101, MAXS = 10001;
const ll INF = 1e18;

int N, L, R, M;
ll A[MAXN];
ll dp[MAXN][MAXS];
ll tmp_dp[MAXN][MAXS];
ll prev_min[MAXN][MAXS];
ll offset_sum = 0;

void init() {
	fastio();
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	M = R - L + 1;

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXS; j++) {
			dp[i][j] = INF;
			tmp_dp[i][j] = INF;
		}
	}
}

int main() {
	init();

	tmp_dp[0][0] = 0;

	for (int i = 0; i < N; i++) {
		offset_sum += (A[i] - L);

		for (int ps = 0; ps <= i * M; ps++) {
			prev_min[0][ps] = tmp_dp[0][ps];
			for (int j = 1; j < M; j++) {
				prev_min[j][ps] = min(prev_min[j - 1][ps], tmp_dp[j][ps]);
			}
		}

		for (int j = 0; j < M; j++) {
			for (int ns = 0; ns <= (i + 1) * M; ns++) {
				dp[j][ns] = INF;

				int ps = ns - j; 
				if (ps >= 0 && ps <= i * M && prev_min[j][ps] != INF) {
					ll diff = ns - offset_sum;
					dp[j][ns] = prev_min[j][ps] + abs(diff);
				}
			}
		}

		memcpy(tmp_dp, dp, sizeof(dp));
	}

	ll ans = INF;

	if (offset_sum >= 0 && offset_sum < MAXS) {
		for (int i = 0; i < M; i++) {
			ans = min(ans, dp[i][offset_sum]);
		}
	}

	if (ans == INF) cout << -1;
	else cout << ans;

	return 0;
}