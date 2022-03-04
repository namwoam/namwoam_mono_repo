from pickle import FALSE


print("萊納，你坐啊")

colossalTitan = input("城牆裡有幾隻超大型巨人?")
print("早上好馬萊，現在我有" + colossalTitan + "隻超大型巨人")

someInteger = 10
someString = "A for apple, B for ball."
someBool = False
someFloat = 8.7

print(1 + 3 * 3)  # ?
print("1" + "3" * 3)  # ?
print(10 / 3)  # ?
print(10 // 3)  # ?
print(2 ** 5)  # ?

print(1 + 3 * 3)  # 10
print("1" + "3" * 3)  # 1333
print(10 / 3)  # 3.3333...
print(10 // 3)  # 3
print(2 ** 5)  # 32

powerYmir = 9999
powerEren = 100
statement1 = powerYmir > powerYmir  # True
yearYmir = 13
yearEren = 13
statement2 = yearEren <= yearYmir  # True

a, b, c, d = 1, 2, 3, 4
firstBool, SecondBool = a = b, c == d
print(firstBool)  # ?
print(SecondBool)  # ?

a, b, c, d = 1, 2, 3, 4
firstBool, SecondBool = a = b, c == d
print(firstBool)  # 2
print(SecondBool)  # False

respondAnytime = True
niceView = True
safe = True
optimalLocation = respondAnytime and niceView \
    and safe  # True

print(not True and False or True or False)  # ?
print(not((True and False) or (True or False)))  # False

erenJoinSurveyCorps = True
erenJoinGarrison = True
erenJoinMilitaryPoliceBrigade = True

if (erenJoinSurveyCorps):
    print("米卡莎加入調查兵團")
elif (erenJoinMilitaryPoliceBrigade):
    print("米卡莎加入憲兵團")
else:
    print("米卡莎加入紮駐兵團")

income = int(input())
tax = 0
if (income < 0):
    tax = 0
elif (income < 100):
    tax = income * 0.1
elif (income < 200):
    tax = income * 0.2
elif (income < 300):
    tax = income * 0.3
else:
    tax = income * 0.4
print(tax)


condition = False
a = 0
if (condition):
    a = 1
else:
    a = -1

condition = False
a = 1 if condition else -1

computer = 10
user = int(input())

if (user > 0):
    if (user > computer):
        print("you win")
else:
    print("you lose")

"""
a, b = 3, 5
if (a > b):
    # a is greater than b
"""
a, b = 3, 5
if (a > b):
    # a is greater than b
    pass

a, b, c = 1, 2, 3
if (c > b):
    if(c > a):
        print("c is the biggest number")

a, b, c = 1, 2, 3
if (c > b and c > a):
    print("c is the biggest number")


