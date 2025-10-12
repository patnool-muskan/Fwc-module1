module dispdec(

input  wire W,
input  wire X,
input  wire Y,
input  wire Z,

output wire a,
output wire b,
output wire c,
output wire d,
output wire e,
output wire f,
output wire g

);


//Display Decoder
always @(*)
begin

a=(!Z&!Y&!X&W)|(!Z&Y&!X&!W);
b=(!Z&Y&!X&W)|(!Z&Y&X&!W);
c=(!Z&!Y&X&!W);
d=(!Z&!Y&!X&W)|(!Z&Y&!X&!W)|(!Z&Y&X&W);
e=(!Z&!Y&!X&W)|(!Z&!Y&X&W)|(!Z&Y&!X&!W)|(!Z&Y&!X&W)|(!Z&Y&X&W)|(Z&!Y&!X&W);
f=(!Z&!Y&!X&W)|(!Z&!Y&X&!W)|(!Z&!Y&X&W)|(!Z&Y&X&W);
g=(!Z&!Y&!X&!W)|(!Z&!Y&!X&W)|(!Z&Y&X&W);

end
endmodule

