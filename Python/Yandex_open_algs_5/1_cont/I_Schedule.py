n = int(input())
year = int(input())

days_of_week = {
    0: "Monday",
    1: "Tuesday",
    2: "Wednesday",
    3: "Thursday",
    4: "Friday",
    5: "Saturday",
    6: "Sunday"
}

days_of_week2 = {
    "Monday": 0,
    "Tuesday": 1,
    "Wednesday": 2,
    "Thursday": 3,
    "Friday": 4,
    "Saturday": 5,
    "Sunday": 6
}

if year % 400 == 0 or (year % 4 == 0 and year % 100 != 0):
    months = {
        "January": 0,
        "February": 31,
        "March": 60,
        "April": 91,
        "May": 121,
        "June": 152,
        "July": 182,
        "August": 213,
        "September": 244,
        "October": 274,
        "November": 305,
        "December": 335
    }
    mas = [53] * 2 + [52] * 5
else:
    months = {
        "January": 0,
        "February": 31,
        "March": 59,
        "April": 90,
        "May": 120,
        "June": 151,
        "July": 181,
        "August": 212,
        "September": 243,
        "October": 273,
        "November": 304,
        "December": 334
    }
    mas = [53] + [52] * 6
for i in range(n):
    day, month = map(str, input().split())
    day = int(day) + months[month] - 1
    mas[day % 7] -= 1
str = input()
sdvig = days_of_week2[str]
min_id = 60
max_id = -1
for i in range(7):
    tmp = mas[i]
    if tmp > max_id:
        max_id = tmp
        max_day = days_of_week[(i + sdvig) % 7]
    if tmp < min_id:
        min_id = tmp
        min_day = days_of_week[(i + sdvig) % 7]
print(max_day, min_day)