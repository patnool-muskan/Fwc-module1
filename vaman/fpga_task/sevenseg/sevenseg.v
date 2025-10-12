module mux_7seg(
    input A, B, C, D,         // Input switches
    output reg [6:0] seg      // 7-Segment display outputs (a,b,c,d,e,f,g)
);

    wire F;
    wire I0, I1, I2, I3;

    // MUX input lines
    assign I0 = C;
    assign I1 = D;
    assign I2 = (~C) | D;
    assign I3 = 1'b0;

    // 4x1 MUX logic
    assign F = (~A & ~B & I0) |
               (~A &  B & I1) |
               ( A & ~B & I2) |
               ( A &  B & I3);

    // Display logic
    always @(*) begin
        case (F)
            1'b0: seg = 7'b0000001; // display '0'
            1'b1: seg = 7'b1001111; // display '1'
            default: seg = 7'b1111111; // off
        endcase
    end
endmodule
