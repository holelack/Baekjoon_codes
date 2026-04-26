#include "bits/stdc++.h"
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, cnt = 0;
    cin >> n;
    vector<int> v(n);
    cin >> v[0];
    bool up = true;
    for(int i = 1; i < n; i++){
        cin >> v[i];
        if(v[i - 1] > v[i] && up){
            cnt++;
            up = false;
        }
        else if(v[i - 1] < v[i] && !up){
            up = true;
        }
    }
    if(cnt && up) cnt++;
    int ans = 0;
    while(cnt){
        cnt = (cnt >> 1) + ((cnt & 1) && (cnt != 1));
        ans++;
    }
    cout << ans;
}