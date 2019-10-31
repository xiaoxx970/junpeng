input_val = input().split(" ")
n = int(input_val[0])# 数组长度
m = int(input_val[1])# 数组最小长度
a = list(map(int, input().split()))
pos = 0
small = 1000000
for pos in range(n-m+1):
    for p in range (n-m+1):
        sum_now = sum(a[pos:pos+m+p])
        if (sum_now < small):
            small = sum_now
print (small)