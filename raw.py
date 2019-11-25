import random
n = int(input())
items = []
# print(n)
for i in range(n):
    club = input()
    # print(club)
    num = int(input())
    # print(num)
    for j in range(num):
        inp = input()
        id = inp[0:6]
        item = inp[7:]
        # print(random.randint(100000,999999),item)
        items.append([item,id])

for item,id in items:
    print(item)
    print(id)
    # print(random.randint(1,26),random.randint(1,11),random.randint(2018,2019))
    print('NOT_ISSUED')
