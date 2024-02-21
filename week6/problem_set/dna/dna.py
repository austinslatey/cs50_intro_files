import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        return

    # TODO: Read database file into a variable
    database_filename = sys.argv[1]
    sequence_filename = sys.argv[2]

    # TODO: Read DNA sequence file into a variable
    database = read_csv(database_filename)

    # TODO: Find longest match of each STR in DNA sequence
    sequence = read_sequence(sequence_filename)

    strs = [key for key in database[0].keys()][1:]
    str_counts = compute_str_counts(sequence, strs)

    # TODO: Check database for matching profiles
    match = find_match(str_counts, database)
    if match:
        print(match)
    else:
        print("No match")

def read_csv(filename):
    """ Reads csv file and returns its contents as a list """
    records = []
    with open(filename, newline="") as file:
        reader = csv.DictReader(file)
        for row in reader:
            records.append(row)
    return records

def read_sequence(filename):
    """ Reads a text file and returns its contents as a string """
    with open(filename, "r") as file:
        return file.read()

def compute_str_counts(sequence, strs):
    """ computes the longest run of consecutive repeats of each STR in the DNA sequence """
    str_counts = {}

    for str in strs:
        str_counts[str] = longest_match(sequence, str)
    return str_counts

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

def find_match(str_counts, database):
    """Find matching profile in the database based on STR counts"""
    for record in database:
        match = True
        for str, count in str_counts.items():
            if int(record[str]) != count:
                match = False
                break
        if match:
            return record["name"]
    return None

main()
