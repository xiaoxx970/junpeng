import sys
t = int(sys.stdin.readline().strip())
for i in range(t):
    n,m = list(map(int, sys.stdin.readline().strip().split()))
    a = list(map(int, sys.stdin.readline().strip().split()))
    print("Case #", i, ":")
    a_mask = [0 for _ in range(n)]
    for j in range(m):
        left, right = list(map(int, sys.stdin.readline().strip().split()))
        for pos in range(n):
            a_mask[pos] += (pos >= left and pos <= right)
    print (a_mask)