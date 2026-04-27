#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}
const int MAXN = 2e3 + 1, INF = 1e9;
int N;
string A, B;
int p1, p3, p5, pp;
int dp[MAXN][MAXN];

void init() {
	fastio();
	cin >> N;
	cin >> A;
	cin >> B;
	A = " " + A;
	B = " " + B;
	cin >> p1 >> p3 >> p5 >> pp;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) dp[i][j] = INF;
	}
	dp[0][0] = 0;
}

int ticket1(int i, int j) {
	int pi = i - 1, pj = j - 1;
	pi = max(pi, 0); pj = max(pj, 0);
	return min(dp[pi][j], dp[i][pj]) + p1;
}

int ticket2(int i, int j) {
	int pi = i - 3, pj = j - 3;
	pi = max(pi, 0); pj = max(pj, 0);
	return min(dp[pi][j], dp[i][pj]) + p3;
}

int ticket3(int i, int j) {
	int pi = i - 5, pj = j - 5;
	pi = max(pi, 0); pj = max(pj, 0);
	return min(dp[pi][j], dp[i][pj]) + p5;
}

int ticket4(int i, int j) {
	if (i != j) return INF;
	int pi = i - 4, pj = j - 4;
	pi = max(0, pi); pj = max(0, pj);
	return dp[pi][pj] + pp;
}

int main() {
	init();

	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			int pi = max(0, i - (A[i] == '0')), pj = max(0, j - (B[j] == '0'));
			dp[i][j] = min({ ticket1(i,j), ticket2(i,j), ticket3(i,j), ticket4(i,j), dp[pi][pj] });
		}
	}

	cout << dp[N][N] << "\n";
	return 0;
}