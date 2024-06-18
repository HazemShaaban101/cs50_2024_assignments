# this program is mario-less in python
# it will print a pyramid


# first we get get_int function for the height of pyramid
from cs50 import get_int

# height is a global variable because we want to retain it after we break from the while loop
height = 0
# this while loop will keep going until user inputs a valid height bigger than zero and equal to or lower than 8
while True:
    height = int(get_int("enter height: "))
    if height > 0 and height <= 8:
        break
    print("wrong height!")


# loop through range from 1 to height, and print line containing spaces and hashes
for i in range(1, height + 1, 1):
    print('        '[0:height - i:1] + '########'[0:i:1])