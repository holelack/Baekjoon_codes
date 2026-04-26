import sys
from math import *

input = sys.stdin.readline
N = int(input())
sq = int(sqrt(N))
seq = list(map(lambda i : int(i) - 1, input().split()))
M = int(input())
query = []
for i in range(M):
    a, b = map(int,input().split()); a-=1; b-=1
    query.append((a,b,i))
query.sort(key = lambda i : (i[0] // sq, i[1]))

Map = [0] * int(1e6)
cur = 0
pa, pb = 0, -1
output = [0] * M
for i in range(M):
    a, b, idx = query[i]
    while pa < a:
        Map[seq[pa]] -= 1
        if Map[seq[pa]] == 0:
            cur -= 1
        pa += 1
    while pa > a:
        pa -= 1
        if Map[seq[pa]] == 0:
            cur += 1
        Map[seq[pa]] += 1
    while pb < b:
        pb += 1
        if Map[seq[pb]] == 0:
            cur += 1
        Map[seq[pb]] += 1
    while pb > b:
        Map[seq[pb]] -= 1
        if Map[seq[pb]] == 0:
            cur -= 1
        pb -= 1
    output[idx] = str(cur)

print("\n".join(output))