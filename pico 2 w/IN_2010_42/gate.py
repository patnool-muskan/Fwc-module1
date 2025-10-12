from machine import Pin
import time

# Define pins
x = Pin(14, Pin.IN, Pin.PULL_DOWN)  # Button X input
y = Pin(15, Pin.IN, Pin.PULL_DOWN)  # Button Y input
z = Pin(13, Pin.OUT)                # LED output

def not_gate(a):
    return int(not a)

def and_gate(a, b):
    return a & b

def or_gate(a, b):
    return a | b

def logic_circuit(x_val, y_val):
    not_x = not_gate(x_val)
    not_y = not_gate(y_val)
    a = and_gate(not_x, y_val)
    b = and_gate(x_val, not_y)
    return or_gate(a, b)

# Initialize previous values
prev_x = prev_y = prev_z = -1  # Invalid initial state to force first print

while True:
    x_val = x.value()
    y_val = y.value()
    z_val = logic_circuit(x_val, y_val)

    # Update output
    z.value(z_val)

    # Only print if something has changed
    if x_val != prev_x or y_val != prev_y or z_val != prev_z:
        print(f"X: {x_val}, Y: {y_val} => Z: {z_val}")
        prev_x, prev_y, prev_z = x_val, y_val, z_val

    time.sleep(0.05)
