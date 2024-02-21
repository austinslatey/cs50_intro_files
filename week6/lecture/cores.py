from cs50 import get_int

cores = []

for i in range(3):
    core = get_int("Core: ")
    # cores.append(core)
    scores += [score]
average = sum(scores) / len(cores)
print(f"Average: {average}")