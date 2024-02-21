from cs50 import get_float

while True:
    dollars = get_float("Change you owe: ")
    if dollars >= 0:
        break

cents = round(dollars * 100)
coins = 0

# num of quarters
coins += cents // 25
cents %= 25

# num of dimes
coins += cents // 10
cents %= 10

coins += cents // 5
cents %= 5

# num of pennies
coins += cents

print(coins)