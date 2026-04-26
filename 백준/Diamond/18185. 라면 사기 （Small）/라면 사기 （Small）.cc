#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
int N;
vector<int> A;

void input() {
    fastio();
    cin >> N;
    A.assign(N, 0);
    for (int& i: A) cin >> i;
}

int main() {
    input();
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < min(N-i, 3) && A[i]; j++) {
            int opType = 1, numOp = A[i];
            for (int k = 0; k < min(N-i,3)-1; k++) {
                if (A[i+k] <= A[i+k+1]) opType++;
                else {
                    numOp = min(A[i], A[i+k] - A[i+k+1]);
                    break;
                }
            }
            ans += (3 + (opType-1)*2) * numOp;
            for (int k = 0; k < opType; k++) {
                A[i+k] -= numOp;
            }
        }
    }
    cout << ans;


    return 0;
}