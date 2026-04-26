#include <bits/stdc++.h>;
using namespace std;
using ll = long long;
#define fastio() {ios::sync_with_stdio(0); cin.tie(0);}

bool solve(int L, int R, int curr, ll prev_jump, int N, const vector<ll>& A) {
    if (L < 0 && R >= N) return true;

    ll distL = (L >= 0) ? (A[curr] - A[L]) : 2e18;
    ll distR = (R < N) ? (A[R] - A[curr]) : 2e18;

    if (distL < distR) {
        if (prev_jump != 0 && distL < 2 * prev_jump) return false;
        return solve(L - 1, R, L, distL, N, A);
    }
    else if (distR < distL) {
        if (prev_jump != 0 && distR < 2 * prev_jump) return false;
        return solve(L, R + 1, R, distR, N, A);
    }
    else {
        bool ok = false;
        if (prev_jump == 0 || distL >= 2 * prev_jump) {
            ok |= solve(L - 1, R, L, distL, N, A);
            if (ok) return true;
            ok |= solve(L, R + 1, R, distR, N, A);
        }
        return ok;
    }
}

int main() {
    fastio();
    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<ll> A(N);
            for (int i = 0; i < N; i++) {
                cin >> A[i];
            }

            vector<string> ans(N, "NO");

            if (N == 1) {
                ans[0] = "YES";
            }
            else {
                ll min_gap = 2e18;
                for (int i = 0; i < N - 1; i++) {
                    min_gap = min(min_gap, A[i + 1] - A[i]);
                }

                int gapCnt = 0;
                vector<int> cand;
                for (int i = 0; i < N - 1; i++) {
                    if (A[i + 1] - A[i] == min_gap) {
                        gapCnt++;
                        cand.push_back(i);
                        cand.push_back(i + 1);
                    }
                }

                if (gapCnt <= 2) {
                    sort(cand.begin(), cand.end());
                    cand.erase(unique(cand.begin(), cand.end()), cand.end());

                    for (int start : cand) {
                        if (solve(start - 1, start + 1, start, 0, N, A)) {
                            ans[start] = "YES";
                        }
                    }
                }
            }

            for (int i = 0; i < N; i++) {
                cout << ans[i] << "\n";
            }
        }
    }
    return 0;
}