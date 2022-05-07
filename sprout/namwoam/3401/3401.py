a, b = map(int, input().split(" "))
totalNeed = (a*(a+1))//2
if b >= totalNeed:
    print("Maow oil enough")
else:
    print("Maow oil not enough")