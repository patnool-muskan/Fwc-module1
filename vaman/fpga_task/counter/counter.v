module counter_7seg(
    input clk,        // Clock input from FPGA (e.g. 12 MHz)
    input rst,        // Reset button (active high)
    output reg [6:0] seg // 7-segment outputs (a,b,c,d,e,f,g)
);

    reg [23:0] count_div;  // Clock divider
    reg [3:0] counter;     // 4-bit counter (0–9)
    wire slow_clk;

    // Clock divider to slow down the blinking rate
    always @(posedge clk or posedge rst) begin
        if (rst)
            count_div <= 0;
        else
            count_div <= count_div + 1;
    end

    // Divide clock frequency
    assign slow_clk = count_div[23];  // Adjust this bit for speed

    // 4-bit counter logic
    always @(posedge slow_clk or posedge rst) begin
        if (rst)
            counter <= 0;
        else if (counter == 9)
            counter <= 0;
        else
            counter <= counter + 1;
    end

    // 7-segment decoder
    always @(*) begin
        case (counter)
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
            default: seg = 7'b1111111; // off
        endcase
    end

endmodule
