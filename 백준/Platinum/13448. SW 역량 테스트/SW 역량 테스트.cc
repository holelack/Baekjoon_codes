#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

typedef struct MPR {
    ll M;
    ll P;
    ll R;
}MPR;

// M_i - t * P_i + M_j - t * P_j;
// i, j => M_i + M_j - t * (P_i + P_j) - R_i * P_j;
// j, i => M_i + M_j - t * (P_i + P_j) - R_j * P_i;
// -R_i * P_j > R_j * P_i => R_i * P_j < R_j * P_i => i,j

bool compare(MPR a, MPR b) {
    return a.R * b.P < b.R * a.P;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T, N;
    cin >> N >> T;
    vector<MPR> seq(N);
    for (auto& i: seq) cin >> i.M;
    for (auto& i: seq) cin >> i.P;
    for (auto& i: seq) cin >> i.R;
    sort(seq.begin(), seq.end(), compare);
    vector<ll> dp(T+1, 0);
    vector<ll> temp = dp;
    for (auto& [M,P,R]: seq) {
        for (int t = R; t <= T; t++)
            temp[t] = max(temp[t], dp[t-R] + M - t * P);
        dp = temp;
    }
    cout << *max_element(dp.begin(), dp.end());

    return 0;
}