#include <bits/stdc++.h>
using namespace std;
#define fastio() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}
#define square(x) (x)*(x)
typedef struct Point {
    int x, y;
    Point(int x, int y): x(x), y(y) {}
    bool operator<(const Point& other) const {
        if (this->x == other.x) return this->y < other.y;
        return this->x < other.x;
    }
} Point;

int n;
vector<Point> P;

void input() {
    fastio();
    cin >> n;
    P.assign(n, Point(0,0));
    for (auto& [x,y]: P) cin >> x >> y;
    sort(P.begin(), P.end());
}

int dist(pair<Point, Point> Points) {
    return square(Points.first.x - Points.second.x) + square(Points.first.y - Points.second.y);
}

pair<Point, Point> bruteForce(int s, int e) {
    auto minPair = make_pair(P[s], P[s+1]);
    for (int i = s; i < e; i++) {
        for (int j = i+1; j <= e; j++) {
            auto p = make_pair(P[i], P[j]);
            if (dist(p) < dist(minPair)) minPair = p;
        }
    }
    return minPair;
}



pair<Point, Point> ClosestPair(int s, int e) {
    int l = e - s + 1;
    if (l <= 3) {
        return bruteForce(s, e);
    }
    int mid = (s + e) >> 1;
    auto CPL = ClosestPair(s, mid);
    auto CPR = ClosestPair(mid+1, e);
    int d = min(dist(CPL), dist(CPR));

    vector<Point> strip;
    for (int i = s; i <= e; i++)
        if (square(P[i].x - P[mid].x) < d) strip.push_back(P[i]);
    sort(strip.begin(), strip.end(), [](Point a, Point b){ return a.y < b.y; });

    auto CPC = CPL;
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i+1; j < strip.size() && square(strip[j].y - strip[i].y) < d; j++) {
            auto p = make_pair(strip[i], strip[j]);
            if (dist(p) < dist(CPC)) CPC = p;
        }
    }
    int DL = dist(CPL), DC = dist(CPC), DR = dist(CPR);
    if (DL <= DC && DL <= DR) return CPL;
    if (DC <= DL && DC <= DR) return CPC;
    if (DR <= DL && DR <= DC) return CPR;
    else return CPC;
}

void solve() {
    input();
    cout << dist(ClosestPair(0,n-1));
}

int main() {
    solve();

    return 0;
}