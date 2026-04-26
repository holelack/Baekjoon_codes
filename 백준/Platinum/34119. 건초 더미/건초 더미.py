import sys
input = sys.stdin.readline
N, Q = map(int,input().split())
D = list(map(int,input().split()))
sortedD = sorted([(i,idx) for idx,i in enumerate(D)])
idxDict = {i:idx for idx,i in enumerate(sortedD)}
cmp = [idxDict[(i,idx)] for idx,i in enumerate(D)]

BIT = [(0,0) for _ in range(N+1)] # (sum, the number of elements)

def sum_query(i):
    res = (0, 0)
    while i > 0:
        res = (res[0] + BIT[i][0], res[1] + BIT[i][1])
        i -= i & -i
    return res

def sum_update(i, x):
    while i <= N:
        BIT[i] = (BIT[i][0] + x, BIT[i][1] + 1)
        i += i & -i

def bisect_query(x):
    l, h = 0, N
    mid = 0
    while l < h:
        mid = (l + h) // 2
        total = sum_query(N)[0] - sum_query(mid)[0]
        if total >= x:
            l = mid + 1
        else:
            h = mid
    return sum_query(N)[1] - sum_query(l-1)[1]

        
queries = []
for i in range(Q):
    x, p = map(int,input().split()); x-=1
    queries.append((x,p,i))
sortedQueries = sorted(queries)

output = [""] * Q
prev = 0
for i in range(Q):
    x, p, qi = sortedQueries[i]
    for j in range(prev, x + 1):
        sum_update(cmp[j] + 1, D[j])
    prev = x + 1
    if sum_query(N)[0] < p:
        output[qi] = "-1"
        continue
    output[qi] = str(bisect_query(p))
sys.stdout.write("\n".join(output))