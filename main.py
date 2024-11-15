n = int(input())
a = list(map(int, input().split()))
m, k = map(int, input().split())
q =  list(map(int, input().split()))
final_pos = [0] * n
cnt_same = [1] * n
for i in range(1, n):
    if a[i]== a[i - 1]:
        cnt_same[i] = cnt_same[i - 1] + 1
    else:
        cnt_same[i] = cnt_same[i - 1]
right = 1
left = 0
while right < n:
    if a[right - 1] > a[right]:
        final_pos[right] = right
        left = right
    else:
        while cnt_same[right] - cnt_same[left] > k:
            left += 1
        final_pos[right] = left
    right += 1
answers = []
for i in range(m):
    answer = final_pos[q[i] - 1] + 1
    answers.append(answer)
print(*answers)