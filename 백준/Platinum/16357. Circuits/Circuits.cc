#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;

const int SIZE = 200001;
int n;
set<int> SET;
vector<int> CC;
vector<tiii> range;
vector<pii> regY[SIZE];
int segTree[SIZE*4], lazy[SIZE*4];

void setLazy(int s, int e, int idx)
{
    int val = lazy[idx];
    lazy[idx] = 0;
    
    segTree[idx] += val;
    if(s != e)
    {
        lazy[idx*2] += val;
        lazy[idx*2+1] += val;
    }
}

void update(int s, int e, int l, int r, int idx, int val)
{
    if(lazy[idx]) setLazy(s, e, idx);
    
    if(e < l || r < s) return;
    if(l <= s && e <= r)
    {
        segTree[idx] += val;
        if(s != e)
        {
            lazy[idx*2] += val;
            lazy[idx*2+1] += val;
        }
        return;
    }
    
    update(s, (s+e)/2, l, r, idx*2, val);
    update((s+e)/2+1, e, l, r, idx*2+1, val);
    segTree[idx] = max(segTree[idx*2], segTree[idx*2+1]);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for(int i=1; i<=n; i++)
	{
	    int ux, uy, vx, vy; cin >> ux >> uy >> vx >> vy;
	    range.push_back({vy, uy, 0});
	    range.push_back({uy, vy, 1});
	    SET.insert(uy), SET.insert(vy);
	}
	
	sort(range.begin(), range.end());
	for(int y : SET) CC.push_back(y);
	
	for(auto [y1, y2, b] : range)
	{
	    y1 = lower_bound(CC.begin(), CC.end(), y1) - CC.begin() + 1;
	    y2 = lower_bound(CC.begin(), CC.end(), y2) - CC.begin() + 1;
	    regY[y1].push_back({y2, b});
	    if(b == 0) update(1, SIZE, y1, y2, 1, 1);
	}
	
	int cross = 0;
	int ans = 0;
	for(int y1=1; y1<SIZE; y1++)
	{
	    for(auto [y2, b] : regY[y1])
	    {
	        if(b == 0)
	        {
	            update(1, SIZE, y1, y2, 1, -1);
	            cross++;
	        }
	    }
	    ans = max(ans, cross + segTree[1]);
	    
	    for(auto [y2, b] : regY[y1])
	        if(b == 1) cross--;
	}
	cout << ans;
}