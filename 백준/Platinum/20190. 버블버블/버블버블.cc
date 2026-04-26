#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
const int INF = 1e9;
int N;
vector<ll> A, lazy, tree, BIT, invs;

void updateBIT(int i, int v) {
    if (!i) return;
    if (i>N) i = N;
    for (; i < BIT.size(); i+=i&-i) {
        BIT[i]+=v;
    }
}

int queryBIT(int i) {
    if (!i) return 0;
    if (i>N) i = N;
    int res = 0;
    for (; i > 0; i-=i&-i) {
        res += BIT[i];
    }
    return res;
}

void prop(int s, int e, int node) {
    if (!lazy[node]) return;
    tree[node] += lazy[node];
    if (s!=e) {
        lazy[node<<1] += lazy[node];
        lazy[node<<1|1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int s, int e, int l, int r, int val, int node) {
    prop(s,e,node);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
        lazy[node] += val;
        prop(s,e,node);
    } else {
        int mid = (s+e)>>1;
        update(s,mid,l,r,val,node<<1);
        update(mid+1,e,l,r,val,node<<1|1);
        tree[node] = min(tree[node<<1], tree[node<<1|1]);
    }
}

ll query(int s, int e, int l, int r, int node) {
    prop(s,e,node);
    if (e < l || r < s) return INF;
    if (l <= s && e <= r) return tree[node];
    int mid = (s+e)>>1;
    return min(query(s,mid,l,r,node<<1), query(mid+1,e,l,r,node<<1|1));
}

void compress() {
    auto tmp = A;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 0; i < N; i++) {
        A[i] = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin();
    }
}

void init() {
    fastio();
    cin >> N;
    A.assign(N, 0);
    for (ll& i: A) cin >> i;
    compress();
    tree.assign(4*N, 0);
    lazy.assign(4*N, 0);
    BIT.assign(N+1, 0);
}

ll inversion() {
    fill(BIT.begin(), BIT.end(), 0);
    ll res = 0;
    for (int i = N - 1; i >= 0; i--) {
        res += queryBIT(A[i]);
        updateBIT(A[i] + 1, 1);
    }
    return res;
}

void upd1(int i) { // update (A[i],N) 1
    if (A[i]==N-1) return;
    update(0, N-1, A[i]+1, N-1, 1, 1);
}

void upd2(int i) { // update (A[i], N) -1
    if (A[i]!=N-1) update(0, N-1, A[i]+1, N-1, -1, 1);
}

void upd3(int i) { // update [0, A[i]) 1
    if (A[i]!=0) update(0, N-1, 0, A[i]-1, 1, 1);
}

int q(int i) {
    return query(0, N-1, 0, N-1, 1) - query(0, N-1, A[i], A[i], 1);
}

int main() {
    init();
    ll inv = inversion();

    for (int i = 0; i < N; i++) {
        upd1(i);
    }

    for (int i = 0; i < N; i++) {
        upd2(i);
        cout << inv + q(i) << " ";
        upd3(i);
    }


    return 0;
}