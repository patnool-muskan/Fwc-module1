module helloworldfpga(
    output wire redled,
    output wire greenled,
    output wire blueled,
                 output a,
                 output b,
                 output c,
             output d,
               output e,
              output f,
               output g

);
    wire clk;

    qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
        .Sys_Clk0 (clk),
    );

    reg[26:0] delay;
     reg	led;


always@(posedge clk) begin
delay = delay+1; //incrementing the counter.
//counts from 0 to 20000000 in 1 second

if(delay > 20000000) //blink delay in decimal
begin
delay=27'b0;
led=0; //keep led on
end
end

assign greenled = !led; //If you want to change led colour to green, 
assign     a=led;
assign     b=led;
assign     c=led;
assign     d=led;
assign     e=!led;
assign     f=led;
assign     g=led;

endmodule
