from cs50 import get_int
import math


# this is the most bruteforce solution i have ever done
# it could be optimized much much further but i still dont know the correct syntax for that
def main():
    card = -1
    # get card number from user
    while card <= 0:
        card = get_int("input card number: ")
    
    card = str(card)
    length = length_check(card)
    card_type = type_of_card(card, length)
    checksum(card, length, card_type)
    
    
def checksum(card, length, card_type):
    # i need to count from behind, if its an odd digit i should simply add it to SUM, if its even i should multiply it by
    # two then add the digits of that multiplication, before adding that to the SUM
    
    # i dont know how to loop through a string from behind so instead if the string is odd lengthed, first digit is treated
    # as an odd digit, if string length is even, first digit is treated as even
    counter = 0
    if length % 2 != 0:
        counter += 1
    SUM = 0
    for i in card:
        if counter % 2 == 0:
            SUM = SUM + (2 * int(i)) % 10 + int((2 * int(i)) / 10)
            counter += 1
        else:
            SUM = SUM + int(i)
            counter += 1
    
    if (SUM % 10 == 0):
        print(card_type)
    else:
        print("INVALID")
        exit()


def type_of_card(card, length):
    # this function returns the expected card type based on length of card number, and the starting digits
    # if the card cannot be a real card, it exits the program without returning anything
    if length == 15 and (int(card[0:2:1]) == 34 or int(card[0:2:1]) == 37):
        return "AMEX"
        
    elif length == 16 and (int(card[0:2:1]) in [51, 52, 53, 54, 55]):
        return "MASTERCARD"
    
    elif (length == 13 or length == 16) and (int(card[0:1:1]) == 4):
        return "VISA"
    else:
        print("INVALID")
        exit()


def length_check(card):
    # this function returns length of card number, it is useful for simply exiting program early when card number length is invalid
    if len(card) in [13, 15, 16]:
        return len(card)
    else:
        print("INVALID")
        exit()


main()