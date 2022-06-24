'''
main() function written by Eric 2 May 2022
'''
import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    people = []
    with open(sys.argv[1], "r") as data:
        reader = csv.DictReader(data)
        for person in reader:
            people.append(person)

    # Read DNA sequence file into a variable
    s = []
    with open(sys.argv[2], "r") as sequence:
        reader = csv.reader(sequence)
        s = sequence.read()

    # Find longest match of each STR in DNA sequence
    # get list of STRs from people list
    headers = list(people[0].keys())[1:]

    # create dictionary of longest STR values found in DNA sequence
    STR_dict = {}
    for i, header in enumerate(headers):
        STR_dict[header] = longest_match(s, header)
    # print(STR_dict)

    # Check database for matching profiles, compare STR counts in DNA sequence with each row (person) in the csv file
    for person in people:
        count = 0
        for STR in STR_dict:
            # print(person["name"], STR_dict[STR], person[STR])
            if STR_dict[STR] != int(person[STR]):
                break
            else:
                count += 1
        if count == len(headers):
            print(person["name"])
            sys.exit(0)
    print("No match")
    return


# longest_match() written by cs50
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

