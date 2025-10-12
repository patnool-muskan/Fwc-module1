module mux_led(
    input A,    // Select line S1
    input B,    // Select line S0
    input C,    // Data input
    input D,    // Data input
    output F    // Output LED
);

    wire I0, I1, I2, I3;
    assign I0 = C;
    assign I1 = D;
    assign I2 = (~C) | D;
    assign I3 = 1'b0;

    // 4x1 MUX implementation
    assign F = (~A & ~B & I0) | 
               (~A &  B & I1) |
               ( A & ~B & I2) |
               ( A &  B & I3);

endmodule
