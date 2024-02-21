def bank_program():
    user_input = input("Type your input: ")

    if user_input == "Hello" or user_input == "Hello, Newman" or user_input == " Hello ":
        print("$0")
    elif user_input == "How you doing?":
        print("$20")
    elif user_input == "What's up?":
        print("$100")
    elif user_input == "What's happening?":
        print("$100")
    else:
        print("Invalid input!")

if __name__ == "__main__":
    bank_program()

