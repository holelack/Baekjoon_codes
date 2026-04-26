import sys
input = sys.stdin.readline
MOD = int(1e9 + 7)
N, Q = map(int,input().split())
operation = [(0,1)]
for _ in range(N):
    cmd, k = input().split()
    if cmd == "+":
        operation.append((int(k),1))
    if cmd == "*":
        operation.append((0,int(k)))

tree = [(0,1)] * (4*N + 4)
def init(s,e,i):
     if s == e:
          tree[i] = operation[s]
          return
     mid = (s + e) // 2
     init(s, mid, i * 2)
     init(mid+1, e, i * 2 + 1)
     tree[i] = ((tree[i*2][0] * tree[i*2+1][1] % MOD + tree[i*2+1][0]) % MOD, tree[i*2][1] * tree[i*2+1][1] % MOD)

def query(s,e,l,r,i):
    if r < s or e < l:
        return (0, 1)
    if l <= s and e <= r:
        return tree[i]
    mid = (s + e) // 2
    op1 = query(s, mid, l, r, i * 2)
    op2 = query(mid + 1, e, l, r, i * 2 + 1)
    return ((op1[0] * op2[1] % MOD + op2[0]) % MOD, op1[1] * op2[1] % MOD)
def update(s,e,i,node,opType,k):
    if node < s or node > e:
        return
    if s == e:
        if opType == "+":
            tree[i] = (k, 1)
        if opType == "*":
            tree[i] = (0, k)
    else:
        mid = (s + e) // 2
        update(s, mid, i * 2, node, opType, k)
        update(mid + 1, e, i * 2 + 1, node, opType, k)
        tree[i] = ((tree[i*2][0] * tree[i*2+1][1] % MOD + tree[i*2+1][0]) % MOD, tree[i*2][1] * tree[i*2+1][1] % MOD)

init(0, N, 1)
output = []
for _ in range(Q):
    i, opType, k = input().split()
    i = int(i)
    k = int(k)
    update(0, N, 1, i, opType, k)
    output.append(str(tree[1][0]))
print("\n".join(output))