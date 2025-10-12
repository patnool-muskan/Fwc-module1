module increment_decoder(
    input A, B, C, D,          // 4-bit binary input from switches
    output reg [6:0] seg       // 7-segment display outputs (a,b,c,d,e,f,g)
);

    wire [3:0] input_num;      // Original input number
    wire [3:0] incremented;    // Incremented result

    assign input_num = {A, B, C, D};   // Combine switches into 4-bit binary
    assign incremented = input_num + 1; // Increment by 1

    // 7-segment decoder for 0–9
    always @(*) begin
        case (incremented)
            4'd0: seg = 7'b0000001; // Display 0
            4'd1: seg = 7'b1001111; // Display 1
            4'd2: seg = 7'b0010010; // Display 2
            4'd3: seg = 7'b0000110; // Display 3
            4'd4: seg = 7'b1001100; // Display 4
            4'd5: seg = 7'b0100100; // Display 5
            4'd6: seg = 7'b0100000; // Display 6
            4'd7: seg = 7'b0001111; // Display 7
            4'd8: seg = 7'b0000000; // Display 8
            4'd9: seg = 7'b0000100; // Display 9
            default: seg = 7'b1111111; // OFF (for values >9)
        endcase
    end

endmodule
