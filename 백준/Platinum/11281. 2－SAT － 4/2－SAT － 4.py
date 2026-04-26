import sys
sys.setrecursionlimit(10**7)
input = sys.stdin.readline

N, M = map(int, input().split())
graph = [[] for _ in range(2 * N)]

def normalized(a):
    return (a - 1) if a > 0 else (N + (-a - 1))

def toggle(u):
    return u + N if u < N else u - N

for _ in range(M):
    a, b = map(int, input().split())
    u = normalized(a)
    v = normalized(b)
    graph[toggle(u)].append(v)
    graph[toggle(v)].append(u)

disc = [-1] * (2 * N)
low = [0] * (2 * N)
on_stack = [False] * (2 * N)
stack = []
time = 0
scc_id = [-1] * (2 * N)
scc_count = 0

def tarjan(u):
    global time, scc_count
    disc[u] = low[u] = time
    time += 1
    stack.append(u)
    on_stack[u] = True

    for v in graph[u]:
        if disc[v] == -1:
            tarjan(v)
            low[u] = min(low[u], low[v])
        elif on_stack[v]:
            low[u] = min(low[u], disc[v])

    if low[u] == disc[u]:
        while True:
            v = stack.pop()
            on_stack[v] = False
            scc_id[v] = scc_count
            if v == u:
                break
        scc_count += 1

for i in range(2 * N):
    if disc[i] == -1:
        tarjan(i)

for i in range(N):
    if scc_id[i] == scc_id[i + N]:
        print(0)
        sys.exit(0)


print(1)

res = []
for i in range(N):
    val = 1 if scc_id[i] < scc_id[i + N] else 0
    res.append(val)
print(*res)
