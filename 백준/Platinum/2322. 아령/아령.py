N = int(input())
load = list(map(int,input().split()))
_min = min(load)

_sorted = sorted(load)
idx = {i : idx for idx,i in enumerate(_sorted)}
cmp = [idx[i] for i in load]

visited = [0] * N
ans = 0
for i in range(N):
    if visited[i]: continue
    cur = i
    cycle = [_sorted[cur]]
    visited[cur] = 1
    while cmp[cur] != i:
        cur = cmp[cur]
        visited[cur] = 1
        cycle.append(_sorted[cur])

    swap_min = 2*(_min + min(cycle)) + (len(cycle) - 1) * _min
    not_swap_min = (len(cycle) - 1) * min(cycle)
    ans += sum(cycle) - min(cycle) + min(swap_min, not_swap_min)

print(ans)