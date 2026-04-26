import sys
input = sys.stdin.readline
print = sys.stdout.write
sys.setrecursionlimit(10**5)
N, Q = map(int, input().split())
parent = [-1]
color = []
for _ in range(N-1):
    parent.append(int(input())-1)
for _ in range(N):
    color.append(int(input()))
par = list(range(N))
sets = [set([i]) for i in color]

def find(x):
    if par[x] != x:
        par[x] = find(par[x])
    return par[x]

def union(a,b):
    ra, rb = find(a), find(b)
    if ra == rb: return
    if len(sets[ra]) < len(sets[rb]):
        ra, rb = rb, ra
    sets[ra].update(sets[rb])
    par[rb] = ra
    sets[rb] = set()

query = []
for _ in range(N + Q - 1):
    cmd, a = map(int,input().split())
    query.append((cmd,a-1))

output = []
while query:
    cmd, a = query.pop()
    if cmd == 1:
        union(a,parent[a])
    if cmd == 2:
        output.append(str(len(sets[find(a)])))
        
print("\n".join(reversed(output)))