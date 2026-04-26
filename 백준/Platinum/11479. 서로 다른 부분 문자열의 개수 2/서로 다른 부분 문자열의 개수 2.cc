#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef pair<int,int> pii;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
string S;
int N, M;
vector<int> sa, isa, nisa, idx, cnt, lcp;

void input() {
    fastio();
    cin >> S;
    N = S.size();
    M = max(256, N) + 1;

    sa.assign(N, 0);
    isa.assign(2*N, 0);
    nisa.assign(2*N, 0);
    lcp.assign(N, 0);
    cnt.assign(M, 0);
    idx.assign(N, 0);
}

void getSA() {
    for (int i = 0; i < N; i++) {
        sa[i] = i;
        isa[i] = S[i];
    }
    for (int k = 1; k < N; k<<=1) {
        auto cmp = [&](int i, int j) {
            if (isa[i] != isa[j]) return isa[i] < isa[j];
            return isa[i+k] < isa[j+k];
        };
        
        for (int i = 0; i < M; i++) cnt[i] = 0;
        for (int i = 0; i < N; i++) cnt[isa[i+k]]++;
        for (int i = 1; i < M; i++) cnt[i] += cnt[i-1];
        for (int i = N-1; i >= 0; i--) idx[--cnt[isa[i+k]]] = i;

        for (int i = 0; i < M; i++) cnt[i] = 0;
        for (int i = 0; i < N; i++) cnt[isa[i]]++;
        for (int i = 1; i < M; i++) cnt[i] += cnt[i-1];
        for (int i = N-1; i >= 0; i--) sa[--cnt[isa[idx[i]]]] = idx[i];

        nisa[sa[0]] = 1;
        for (int i = 1; i < N; i++) {
            nisa[sa[i]] = nisa[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        for (int i = 0; i < N; i++) isa[i] = nisa[i];
        if (isa[sa[N-1]] == N) break;
    }
}

void getLCP() {
    for (int i = 0; i < N; i++) isa[sa[i]] = i;
    int r = 0;
    for (int i = 0; i < N; i++) {
        if (isa[i]) {
            while (S[sa[isa[i]-1]+r] == S[i+r]) r++;
            lcp[isa[i]] = r ? r-- : 0;
        }
    }
}

int main() {
    input();
    getSA();
    getLCP();
    ll sum = 0;
    for (int i = 0; i < N; i++) sum += lcp[i];
    cout << (ll)N*(N+1)/2 - sum;

    
    return 0;
}