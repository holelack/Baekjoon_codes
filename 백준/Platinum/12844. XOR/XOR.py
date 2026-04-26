import sys
input = sys.stdin.readline
N = int(input())
seq = list(map(int,input().split()))

tree = [0]*(4*N)
lazy = [0]*(4*N)

def init(node=1,s=0,e=N-1):
    if s==e:
        tree[node] = seq[s]
        return tree[node]
    mid = (s+e)//2
    tree[node] = init(node*2,s,mid) ^ init(node*2+1,mid+1,e)
    return tree[node]

def propagate(node,s,e):
    if lazy[node] != 0:
        tree[node] ^= lazy[node] if (e-s+1)%2 else 0
        if s != e:
            lazy[node*2] ^= lazy[node]
            lazy[node*2+1] ^= lazy[node]
        lazy[node] = 0

def update(node,s,e,l,r,diff):
    propagate(node,s,e)
    if e<l or r<s:
        return
    if l<=s<=e<=r:
        #propagate only once with diff
        tree[node] ^= diff if (e-s+1)%2 else 0
        if s!=e:
            lazy[node*2] ^= diff
            lazy[node*2+1] ^= diff
        return
    mid = (s+e)//2
    update(node*2,s,mid,l,r,diff); update(node*2+1,mid+1,e,l,r,diff)
    tree[node] = tree[node*2] ^ tree[node*2+1]

def query(node,s,e,l,r):
    propagate(node,s,e)
    if e<l or r<s:
        return 0
    if l<=s<=e<=r:
        return tree[node]
    mid = (s+e)//2
    return query(node*2,s,mid,l,r) ^ query(node*2+1,mid+1,e,l,r)

init()

M = int(input())
for i in range(M):
    cmd,*q = map(int,input().split())
    if cmd==1:
        update(1,0,N-1,q[0],q[1],q[2])
    if cmd==2:
        print(query(1,0,N-1,q[0],q[1]))