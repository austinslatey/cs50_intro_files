menu = {
    "Taco": 7.50,
    "Baja Taco": 8.75,
    "Taco Salad": 7.99
}

total = 0

while True:
    try:
        item = input("Please enter something from the menu")
    # be sure to account for error using KeyError
    except EOFError:
        break

    if item in menu:
        total += menu[item]
        print(f"Total for this order is ${total:.2f}")
    else:
        print("Invalid Item")
