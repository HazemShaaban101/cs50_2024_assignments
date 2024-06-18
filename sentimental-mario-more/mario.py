def main():
    user_input = 0
    # loop until user inputs a valid height between 1 and 8
    while user_input <= 0 or user_input > 8:
        user_input = get_int("Enter height: ")

    # for the range of height the user input
    for i in range(1, user_input + 1, 1):
        # print one space times the height - i, then print hash i times, then two spaces, then hash i times
        print(" " * (user_input - i) + "#" * i + "  " + "#" * i)
  

def get_int(message):
    while True:
        try:
            return int(input(message))
        except ValueError:
            pass


main()