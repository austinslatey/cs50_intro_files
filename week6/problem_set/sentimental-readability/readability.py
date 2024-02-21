from cs50 import get_string

text = get_string("Text: ")

# Count number of letters, words, and sentences
letters = sum(1 for char in text if char.isalpha())
words = len(text.split())
sentences = sum(1 for char in text if char in [".", "!", "?"])

# calculate the average number of letters and sentences per 100 words
l = (letters / words) * 100
s = (sentences / words) * 100

# calculate coleman-liau
index = 0.0588 * l - 0.296 * s - 15.8

# determine the grade level
grade = round(index)

# print the grade level
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")
