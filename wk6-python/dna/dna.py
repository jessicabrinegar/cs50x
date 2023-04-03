import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], newline='') as db_file:
        reader = csv.DictReader(db_file)
        data = []
        for row in reader:
            data.append(row)
        STRs = list(data[0].keys())
        name_index = STRs.index("name")
        STRs.pop(name_index)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], newline='') as dna_file:
        reader = csv.reader(dna_file)
        for row in reader:
            dna = row
        sequence = dna[0]

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for subsequence in STRs:
        match_length = longest_match(sequence, subsequence)
        matches[subsequence] = match_length

    # TODO: Check database for matching profiles
    for person in data:
        name = person.pop("name")
        match_count = 0
        for subsequence in person:
            if matches[subsequence] == person[subsequence]:
                match_count += 1
        if match_count == len(STRs):
            return print(f"{name}")
        else:
            continue

    print("No match.")
    sys.exit(0)


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
    return str(longest_run)


main()