from collections import deque
import sys
input = sys.stdin.readline
print = sys.stdout.write
T = int(input())

output = []
for _ in range(T):
    N = int(input())
    S = input()
    l = N
    count = deque()
    prev = -1
    cnt = 0
    for i in range(N):
        if prev == -1:
            cnt+=1
            prev = S[i]
            continue
        if prev != S[i]:
            count.append((prev,cnt))
            cnt = 1
            prev = S[i]
            continue
        if prev == S[i]:
            cnt+=1
    count.append((prev,cnt))
    start = 0
    firstzeros = 0
    if count[0][0] == '0':
        start += count[0][1]
        firstzeros = count[0][1]
        N -= count.popleft()[1]
    if len(count) == 1:
        if S[0] == '1':
            output.append("1"*(N-1)); output.append("0\n")
        else:
            output.append("1"*N); output.append("\n")
        continue
    if len(count) == 0:
        output.append("0\n")
        continue
    if count[0][1] >= count[1][1]:
        start += count[0][1] - count[1][1]
    output.append("1"*count[0][1])
    for i in range(N-count[0][1]):
        if S[firstzeros + count[0][1]+i] == S[start+i]:
            output.append("0")
        else:
            output.append("1")
    output.append("\n")
print("".join(output))