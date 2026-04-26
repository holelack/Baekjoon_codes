import bisect, sys, math
input = sys.stdin.readline
print = sys.stdout.write
N = int(input())
jump = []
for i in range(N):
    a, b = map(int,input().split())
    jump.append((a,b))
jump.sort()
# get graph
graph = [float('inf') for _ in range(N)]
for i in range(N):
    x,p = jump[i]
    res = 0
    ndouble = 0
    if i==N-1:
        graph[i] = (-1,float('inf'))
        continue
    _next = i
    while True:
        dist = p * (2 ** ndouble)
        if x + dist >= jump[i+1][0]:
            _next = bisect.bisect_right(jump, (x + dist,float('inf'))) - 1
        res += x + dist - jump[_next][0] + 1
        ndouble += 1
        if _next != i:
            break
    graph[i] = (_next, res)
# get sparse table and dists
MAX = math.ceil(math.log2(N))
sparse_table = [[float('inf')] * MAX for _ in range(N)]
sparse_dist = [[float('inf')] * MAX for _ in range(N)]
for level in range(MAX):
    for i in range(N):
        if level == 0:
            _next, res = graph[i]
            sparse_table[i][level] = _next
            sparse_dist[i][level] = res
            continue
        sparse_table[i][level] = sparse_table[sparse_table[i][level-1]][level-1]
        sparse_dist[i][level] = sparse_dist[sparse_table[i][level-1]][level-1] + sparse_dist[i][level-1]
# query
output = []
Q = int(input())
for i in range(Q):
    s,t = map(int,input().split())
    if s < jump[0][0]:
        output.append(str(s-t))
        continue
    cur = bisect.bisect_right(jump, (s,float('inf'))) - 1
    time = 0
    time += s - jump[cur][0]
    if time >= t:
        output.append(str(s-t))
        continue
    for i in range(MAX-1,-1,-1):
        temp = sparse_dist[cur][i]
        if temp > t - time:
            continue
        time += temp
        cur = sparse_table[cur][i]
    pos = jump[cur][0]
    x,p = jump[cur]
    ndouble = 0
    _next = cur
    while True:
        dist = p * (2 ** ndouble)
        if cur != N-1 and pos + dist >= jump[cur+1][0]:
            _next = bisect.bisect_right(jump, (pos + dist,float('inf'))) - 1
        if t - time < 1:
            break
        time += 1
        pos += dist
        if t - time < x + dist - jump[_next][0]:
            pos = pos - (t - time)
            break
        time += x + dist - jump[_next][0]
        pos -= x + dist - jump[_next][0]
        ndouble += 1
    output.append(str(pos))
print("\n".join(output))
