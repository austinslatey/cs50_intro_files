while True:
    try:
        height = int(input("Height: "))
        if height < 1 or height > 8:
            print("Please enter a number between 1 and 8.")
        else:
            break
    except ValueError:
        print("Please enter a numeric value for the height.")


for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i)