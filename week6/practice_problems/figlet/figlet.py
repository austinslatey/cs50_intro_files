import sys
import pyfiglet

def print_error_message():
    print("invalid usage")
    sys.exit(1)

def figlet_program():
    if len(sys.argv) not in [1, 3]:
        print_error_message()

    if len(sys.argv) == 3:
        flag = sys.argv[1]

        if flag not in ['-f', '--font']:
            print_error_message()
    else:
        font = None

    text = input("Enter text")

    figlet = pyfiglet.Figlet(font=font)
    ascii_art = figlet.renderText(text)
    print(ascii_art)

if __name__ == "__main__":
    figlet_program()


