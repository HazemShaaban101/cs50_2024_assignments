from cs50 import get_float
import math


def main():
    # coin counter
    coins = 0
    change = -1
    # loop until user inputs a valid change number
    while change < 0:
        change = get_float("change: ")
    # loop over the value, decreasing it by a quarter and increasing coin count by one, until the value is less than a quarter
    while change >= 0.25:
        change = round(change - 0.25, 2)
        coins += 1
    # loop over the value, decreasing it by a dime and increasing coin count by one, until the value is less than a dime
    while change >= 0.10:
        change = round(change - 0.10, 2)
        coins += 1
    # loop over the value, decreasing it by a nickel and increasing coin count by one, until the value is less than a nickel
    while change >= 0.05:
        change = round(change - 0.05, 2)
        coins += 1
    # loop over the value, decreasing it by a penny and increasing coin count by one, until the value is less than a penny
    while change >= 0.01:
        change = round(change - 0.01, 2)
        coins += 1
        
    print(coins)


main()