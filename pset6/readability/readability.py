from cs50 import get_string

def main():
    text = get_string("Text: ")
    letter = count_letter(text)
    word = count_word(text)
    sentence = count_sentence(text)

    L = (100 / word) * letter
    S = (100 / word) * sentence

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")

def count_letter(text):
    counter = 0
    for letter in text:
        if letter >= 'A' and letter <= 'z':
            counter += 1
    return counter

def count_word(text):
    counter = 0
    for space in text:
        if space == " ":
            counter += 1
    counter += 1
    return counter

def count_sentence(text):
    counter = 0
    for sentence in text:
        if sentence == "." or sentence == "!" or sentence == "?":
            counter += 1
    return counter


if __name__ == "__main__":
    main()