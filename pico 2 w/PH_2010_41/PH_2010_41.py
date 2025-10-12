
from machine import Pin
from time import sleep

# Logic gate definitions
def XOR(a, b):
    return a ^ b

def NOT(x):
    return 1 - x

def AND(a, b):
    return a & b

def OR(a, b):
    return a | b

print("For any set of inputs A and B, the given circuit gives same output Q, except one. Which one is it?\n")

# Circuit (A)
print("(A)")
print("A B | A⊕B | B' | (A⊕B)∧B'")
print("--------------------------")
for a in [0, 1]:
    for b in [0, 1]:
        xor = XOR(a, b)
        b_bar = NOT(b)
        result = AND(xor, b_bar)
        print(f"{a} {b} |  {xor}  |  {b_bar} |     {result}")
print()

# Circuit (B)
print("(B)")
print("A B | B' | A∧B'")
print("----------------")
for a in [0, 1]:
    for b in [0, 1]:
        b_bar = NOT(b)
        result = AND(a, b_bar)
        print(f"{a} {b} | {b_bar} |   {result}")
print()

# Circuit (C)
print("(C)")
print("A B | B' | A∧B' | (A∧B')∧B | A∧B' + (A∧B')∧B")
print("---------------------------------------------")
for a in [0, 1]:
    for b in [0, 1]:
        b_bar = NOT(b)
        ans = AND(a, b_bar)
        ans1 = AND(ans, b)
        result = OR(ans, ans1)
        print(f"{a} {b} | {b_bar} |   {ans}   |     {ans1}     |        {result}")
print()

# Circuit (D)
print("(D)")
print("A B | A' | A'+B")
print("------------------")
for a in [0, 1]:
    for b in [0, 1]:
        a_bar = NOT(a)
        result = OR(a_bar, b)
        print(f"{a} {b} | {a_bar} |   {result}")
print()

# Optional: Blink LED if a mismatch pattern is found (e.g. in part C, unique result)
led = Pin("LED", Pin.OUT)
for _ in range(3):
    led.on()
    sleep(0.15)
    led.off()
    sleep(0.15)
