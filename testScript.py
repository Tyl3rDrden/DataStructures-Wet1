import subprocess
import random

# Number of operations to perform
num_operations = 20

# Range of values to insert/delete
value_range = 100

# Generate a sequence of insert and delete commands
commands = []
for _ in range(num_operations):
    command = random.choice(["insert", "delete"])
    value = random.randint(0, value_range)
    commands.append(command)
    commands.append(str(value))

# Add a print command at the end to see the final tree
commands.append("print")

# Run the main.cpp program with the generated commands
subprocess.run(["./main"] + commands)
