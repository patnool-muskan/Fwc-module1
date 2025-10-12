from machine import Pin
from time import sleep

# Optional: Use onboard LED to indicate F = 1
led = Pin("LED", Pin.OUT)

# Logic gate definitions
def not_gate(x):
    return int(not x)

def and_gate(x, y):
    return x & y

# 4x1 MUX function
def mux_4x1(A, B, C, D):
    I0 = C
    I1 = D
    I2 = not_gate(C)
    I3 = and_gate(not_gate(C), not_gate(D))

    select = (A << 1) | B
    inputs = [I0, I1, I2, I3]
    return inputs[select]

# Main loop to evaluate all inputs
minterms = []
print("A B C D => F")

for A in [0, 1]:
    for B in [0, 1]:
        for C in [0, 1]:
            for D in [0, 1]:
                F = mux_4x1(A, B, C, D)
                index = (A << 3) | (B << 2) | (C << 1) | D
                print(f"{A} {B} {C} {D} => {F}")
                
                if F == 1:
                    minterms.append(index)
                    # Blink LED to show F=1
                    led.value(1)
                    sleep(0.1)
                    led.value(0)
                else:
                    led.value(0)
                sleep(0.05)  # Delay for readability

# Final minterm result
print("\nMinterms where F = 1:")
print(f"F = Σm{tuple(minterms)}")
