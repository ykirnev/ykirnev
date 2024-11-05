n, k = map(int, input().split())
a = list(map(int, input().split()))
pr = {0 :1}
tmpsum = 0
for x in a:
    tmpsum += x
    if tmpsum not in pr:
        pr[tmpsum] = 0
    pr[tmpsum] += 1
cnt = 0
for i in pr:
    if (i + k) in pr:
        cnt += 1
print(cnt)

