import csv

with open("phonebook.csv", "a")
    name = input("Name: ")
    number = input("Number: ")

    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow([name, number])

