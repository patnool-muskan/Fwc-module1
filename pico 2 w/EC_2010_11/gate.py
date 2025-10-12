from machine import Pin
from time import sleep

# Define NOT gate
def NOT(a):
    return 1 - a

# Define the 8 logic gates
def first(a, b):
    return NOT(a | b)  # NOR

def second(a, b):
    return NOT(a & b)  # NAND

def third(a, b):
    return a ^ b       # XOR

def fourth(a, b):
    return NOT(a ^ b)  # XNOR

def fifth(a, b):
    return a ^ NOT(b)  # Custom

def sixth(a, b):
    return NOT(a) | NOT(b)  # DeMorgan NAND

def seventh(a, b):
    return NOT(NOT(a) ^ b)  # Custom XNOR variant

def eighth(a, b):
    return NOT(a) & NOT(b)  # DeMorgan NOR

# Store all gates in a dictionary
gates = {
    '1st': first,
    '2nd': second,
    '3rd': third,
    '4th': fourth,
    '5th': fifth,
    '6th': sixth,
    '7th': seventh,
    '8th': eighth
}

# All 2-bit input combinations
inputs = [(0, 0), (0, 1), (1, 0), (1, 1)]

# To store truth tables
truth_tables = {}

# Begin output
print("Truth Tables for Logic Gates:\n")

# Evaluate all gates
for name, func in gates.items():
    table = []
    print(f"{name} Gate")
    print("A B | OUT")
    for a, b in inputs:
        out = func(a, b)
        table.append(out)
        print(f"{a} {b} |  {out}")
    truth_tables[name] = table
    print()

# Compare and display matching gates
print("Matching Gate Outputs:\n")
matched = set()

for g1 in truth_tables:
    for g2 in truth_tables:
        if g1 != g2 and truth_tables[g1] == truth_tables[g2]:
            pair = tuple(sorted((g1, g2)))
            if pair not in matched:
                print(f"{g1} == {g2}")
                matched.add(pair)

# Optional: Blink onboard LED after execution
led = Pin("LED", Pin.OUT)
for _ in range(3):
    led.toggle()
    sleep(0.2)
    led.toggle()
    sleep(0.2)
