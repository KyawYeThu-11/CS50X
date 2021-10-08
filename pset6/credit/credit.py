from cs50 import get_int

def main():
    number = get_int("Number: ")

    number_1 = number
    number_2 = int(number / 10)

    firstTwo = number
    firstOne = 0

    sum_1 = 0
    sum_2 = 0

    length = len(str(number))

    #Getting firstTwo & firstOne
    while firstTwo >= 100:
        firstTwo = int(firstTwo / 10)
    firstOne = int(firstTwo / 10)

    #From last digit
    while number_1 > 0:
        lastDigit = number_1 % 10
        sum_1 += lastDigit
        number_1 = int(number_1 / 100)

    #From second-last digit
    while number_2 > 0:
        lastDigit = number_2 % 10
        sum_2 += magic(lastDigit)
        number_2 = int(number_2 / 100)

    total = sum_1 + sum_2
    if total % 10 == 0:

        if length >= 13 and length <= 16:

            if firstTwo == 34 or firstTwo == 37:
                print("AMEX")

            elif firstTwo >= 51 and firstTwo <= 55:
                print("MASTERCARD")

            elif firstOne == 4:
                print("VISA")

            else:
                print("INVALID")

        else:
            print("INVALID")

    else:
        print("INVALID")


def magic(lastDigit):
    lastDigit *= 2
    if lastDigit >= 10:
        first = int(lastDigit / 10)
        second = lastDigit % 10
        result = first + second
        return result
    else:
        return lastDigit

if __name__ == "__main__":
    main()