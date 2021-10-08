from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

far = height - 1
hashes = 1

for h in range(height):
    for f in range(far):
        print(" ", end = "")

    for h in range(hashes):
        print("#", end = "")

    print("  ", end = "")

    for h in range(hashes):
        print("#", end = "")

    print(end="\n")
    hashes += 1
    far -= 1
