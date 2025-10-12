module display_decoder(
    input A, B, C, D,          // 4-bit input (from switches)
    output reg [6:0] seg       // 7-segment display outputs (a,b,c,d,e,f,g)
);

    wire [3:0] input_num;
    assign input_num = {A, B, C, D};   // Combine into 4-bit binary

    // 7-segment decoder logic
    always @(*) begin
        case (input_num)
            4'd0: seg = 7'b0000001; // 0
            4'd1: seg = 7'b1001111; // 1
            4'd2: seg = 7'b0010010; // 2
            4'd3: seg = 7'b0000110; // 3
            4'd4: seg = 7'b1001100; // 4
            4'd5: seg = 7'b0100100; // 5
            4'd6: seg = 7'b0100000; // 6
            4'd7: seg = 7'b0001111; // 7
            4'd8: seg = 7'b0000000; // 8
            4'd9: seg = 7'b0000100; // 9
            default: seg = 7'b1111111; // Blank for >9
        endcase
    end

endmodule
