n = int(input().strip())
a = list(map(int, input().strip().split()))
m, k = map(int, input().strip().split())
asks = list(map(int, input().strip().split()))
final_positions = [0] * n
count_same = [1] * n
for i in range(1, n):
    if a[i] == a[i - 1]:
        count_same[i] = count_same[i - 1] + 1
    else:
        count_same[i] = count_same[i - 1]
i = 1
left = 0
while i < n:
    if a[i - 1] > a[i]:
        final_positions[i] = i
        left = i
    else:
        while count_same[i] - count_same[left] > k:
            left += 1
        final_positions[i] = left
    i += 1
for i in range(m):
    print(final_positions[asks[i] - 1] + 1, end = ' ')
