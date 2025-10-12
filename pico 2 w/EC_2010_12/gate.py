
from machine import Pin
from time import sleep

# Define logic gates
def or_gate(a, b):
    return a | b

def nor_gate(a, b):
    return int(not (a | b))

def final_or_gate(a, b):
    return a | b

# Define the logic circuit
def logic_circuit(A, B, C):
    out1 = or_gate(A, B)       # First OR gate
    out2 = nor_gate(A, B)      # NOR gate
    F = final_or_gate(out1, C) & final_or_gate(out2, C)
    return F

# Display header
print("A B C => F\n")

# Test all input combinations
for A in [0, 1]:
    for B in [0, 1]:
        for C in [0, 1]:
            F = logic_circuit(A, B, C)
            print(f"{A} {B} {C} => {F}")

# Final answer as per logic
print("\nCorrect Answer: A=0, B=0, C=1")

# Optional: Blink LED if correct condition is met
led = Pin("LED", Pin.OUT)
if logic_circuit(0, 0, 1) == 1:
    for _ in range(3):  # Blink LED 3 times
        led.toggle()
        sleep(0.2)
        led.toggle()
        sleep(0.2)
