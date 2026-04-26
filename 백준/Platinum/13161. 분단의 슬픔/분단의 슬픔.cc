#include <bits/stdc++.h>
using namespace std;

int c[555][555];
int f[555][555];
vector<int> g[555];
int lv[555];
int work[555];
int chk[555];
int n;
int s = 501, t = 502;

bool bfs(){
	memset(lv, -1, sizeof lv);
	queue<int> q; q.push(s);
	lv[s] = 0;
	while(q.size()){
		int now = q.front(); q.pop();
		for(auto nxt : g[now]){
			if(lv[nxt] == -1 && c[now][nxt] - f[now][nxt] > 0){
				lv[nxt] = lv[now] + 1;
				q.push(nxt);
			}
		}
	}
	return lv[t] != -1;
}

int dfs(int now, int tot){
	if(now == t) return tot;
	for(int &i=work[now]; i<g[now].size(); i++){
		int nxt = g[now][i];
		if(lv[nxt] == lv[now] + 1 && c[now][nxt] - f[now][nxt] > 0){
			int fl = dfs(nxt, min(tot, c[now][nxt] - f[now][nxt]));
			if(fl > 0){
				f[now][nxt] += fl;
				f[nxt][now] -= fl;
				return fl;
			}
		}
	}
	return 0;
}

void decom(){
	queue<int> q; q.push(s);
	chk[s] = 1;
	while(q.size()){
		int now = q.front(); q.pop();
		for(auto nxt : g[now]){
			if(!chk[nxt] && c[now][nxt] - f[now][nxt] > 0){
				chk[nxt] = 1;
				q.push(nxt);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for(int i=1; i<=n; i++){
		int x; cin >> x;
		if(x == 1){
			c[s][i] = 1e9+7;
			g[s].push_back(i);
			g[i].push_back(s);
		}
		if(x == 2){
			c[i][t] = 1e9+7;
			g[i].push_back(t);
			g[t].push_back(i);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			cin >> c[i][j];
			if(i != j) g[i].push_back(j);
		}
	}

	int ans = 0;
	while(bfs()){
		memset(work, 0, sizeof work);
		while(1){
			int fl = dfs(s, 1e9+7);
			if(!fl) break;
			ans += fl;
		}
	}
	cout << ans << "\n";

	decom();
	vector<int> a, b;
	for(int i=1; i<=n; i++){
		if(chk[i]) a.push_back(i);
		else b.push_back(i);
	}
	for(auto i : a) cout << i << " "; cout << "\n";
	for(auto i : b) cout << i << " "; cout << "\n";
}