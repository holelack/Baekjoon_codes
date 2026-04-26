import math, sys
input = sys.stdin.readline
T = int(input())
def CCW(o,a,b):
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

def dist(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2

def getConvexHull(P):
    lower = []
    for p in P:
        while len(lower) >= 2 and CCW(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    upper = []
    for p in reversed(P):
        while len(upper) >= 2 and CCW(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)
    
    return lower[:-1] + upper[:-1]

def diameter(hull):
    L = len(hull)
    if L == 2:
        return dist(hull[0], hull[1]), (hull[0], hull[1])
    
    _max = 0
    maxPair = []

    j = 1
    for i in range(L):
        ni = (i + 1) % L
        while True:
            nj = (j + 1) % L
            cur = abs(CCW(hull[i], hull[ni], hull[j]))
            nxt = abs(CCW(hull[i], hull[ni], hull[nj]))
            if nxt > cur:
                j = nj
            else:
                break
        for u, v in [(hull[i], hull[j]), (hull[ni], hull[j])]:
            d = dist(u ,v)
            if d > _max:
                _max = d
                maxPair = (u, v)
    return _max, maxPair

for _ in range(T):
    N = int(input())
    P = []
    for _ in range(N):
        x, y = map(int,input().split())
        P.append((x,y))
    P.sort()
    p1, p2 = diameter(hull:=getConvexHull(P))[1]
    print(*p1,*p2)