import sys
input = sys.stdin.readline
N = int(input())

P = []
for _ in range(N):
    x1,y1,x2,y2 = map(int,input().split())
    P.append((x1,y1,y2,0))
    P.append((x2,y1,y2,1))

P.sort()

segtree1 = [0] * 120005
cover = [0] * 120005

def update(s, e, l, r, node, val):
    if r <= s or e <= l:
        return
    if l <= s and e <= r:
        cover[node] += val
    else:
        mid = (s + e) // 2
        update(s, mid, l, r, node*2, val)
        update(mid, e, l, r, node*2+1, val)

    if cover[node] > 0:
        segtree1[node] = e - s
    else:
        if s+1 == e:
            segtree1[node] = 0
        else:
            segtree1[node] = segtree1[node*2] + segtree1[node*2+1]

prev = P[0][0]
ans = 0
for x,y1,y2,_type in P:
    ans += (x - prev) * segtree1[1]
    if _type == 0:
        update(0, 30001, y1, y2, 1, 1)
    else:
        update(0, 30001, y1, y2, 1, -1)
    prev = x

print(ans)
