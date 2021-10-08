import csv
import sys

def main():

    database = []
    dna = {}
    STRs = []

    #Checking the number of command-line arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    #filling database
    with open(sys.argv[1], "r") as data_file:
        reader = csv.DictReader(data_file)
        for row in reader:
            database.append(row)

    #filling types of STR according to database
    with open(sys.argv[1], "r") as data_file:
        reader_2 = csv.reader(data_file)
        for row in reader_2:
            for column in row:
                if column == "name":
                    continue
                else:
                    STRs.append(column)
            break;

    #filling maximum counts of each STR from a sequence in dictionary called "dna"
    for STR in STRs:
        with open(sys.argv[2], "r") as sequence_file:
            repeated_number = repetition(sequence_file, STR)
            dna[STR] = repeated_number

    #matching dna data with each person from database
    for person in database:
        found = False
        for STR in STRs:
            if int(person[STR]) == dna[STR]:
                found = True
                continue
            else:
                found = False
                break
        if found == True:
            print(person["name"])
            break
        else:
            continue

    if found == False:
        print("No match")

#finding maximum count of a certain STR from the sequence
def repetition(sequence_file, STR):
    sequence = sequence_file.read()

    counts= []
    index = 0

    while index < len(sequence):
        counter = 0
        temp_index = index
        while True:
            found = False
            for i in range(len(STR)):
                if temp_index >= len(sequence):
                    break
                else:
                    if sequence[temp_index] == STR[i]:
                        temp_index += 1
                        found = True
                        continue
                    else:
                        found = False
                        break

            if found == True:
                counter += 1
            else:
                break
        index += 1
        counts.append(counter)

    return max(counts)


if __name__ == "__main__":
    main()