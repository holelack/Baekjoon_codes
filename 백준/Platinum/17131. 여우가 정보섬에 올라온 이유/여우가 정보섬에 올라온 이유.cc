#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7, INF = 1e18;
int N,Y;
vector<pair<long long,long long>> stars;

vector<long long> BIT1, BIT2;

void update1(int i, long long val) {
    for (; i < BIT1.size(); i+=(i&-i))
        BIT1[i] = (BIT1[i]+val) % MOD;
}

void update2(int i, long long val) {
    for (; i < BIT2.size(); i+=(i&-i)) 
        BIT2[i] = (BIT2[i]+val) % MOD;
}

long long query1(int i) {
    long long res = 0;
    for (; i > 0; i-=(i&-i))
        res+=BIT1[i];
    return res % MOD;
}

long long query2(int i) {
    long long res = 0;
    for (; i > 0; i-=(i&-i))
        res+=BIT2[i];
    return res % MOD;
}

int main() {
    cin >> N;
    vector<int> Ycmp;
    int temp;
    for (int i = 0; i < N; i++) {
        stars.emplace_back();
        cin >> stars[i].first >> stars[i].second;
        Ycmp.emplace_back(stars[i].second);
    }
    sort(Ycmp.begin(), Ycmp.end());
    Ycmp.erase(unique(Ycmp.begin(), Ycmp.end()), Ycmp.end());
    Y = Ycmp.size();
    for (int i = 0; i < N; i++)
        stars[i].second = lower_bound(Ycmp.begin(), Ycmp.end(), stars[i].second) - Ycmp.begin() + 1;
    
    sort(stars.begin(), stars.end());
    BIT1.assign(Y+1, 0); // counting sum of down segments
    BIT2.assign(Y+1, 0); // counting up segments
    long long ans = 0;
    vector<pair<long long,long long>> tempV1, tempV2;
    long long prev = -INF;
    for (auto& [x,y]: stars) {
        if (prev < x) {
            for (auto& [y,val]: tempV1) update1(y,val);
            for (auto& [y,val]: tempV2) update2(y,val);
            tempV1.clear(); tempV2.clear();
        }
        long long up = (query2(Y) - query2(y)) % MOD;
        long long down = query1(y-1) % MOD;
        ans += down;

        tempV1.emplace_back(make_pair(y,up));
        tempV2.emplace_back(make_pair(y,1));
        prev = x;
    }
    cout << ans % MOD;
    return 0;
}