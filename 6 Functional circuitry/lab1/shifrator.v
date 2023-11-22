`timescale 1ns / 1ps

    module shifrator(
        input [7:0] a,
        output q1,
        output q2,
        output q4
    );
    
    or_by_nand quit1(.a0(a[1]), .a1(a[3]), .a2(a[5]), .a3(a[7]), .res(q1));
    or_by_nand quit2(.a0(a[2]), .a1(a[3]), .a2(a[6]), .a3(a[7]), .res(q2));
    or_by_nand quit3(.a0(a[4]), .a1(a[5]), .a2(a[6]), .a3(a[7]), .res(q4));
    
endmodule