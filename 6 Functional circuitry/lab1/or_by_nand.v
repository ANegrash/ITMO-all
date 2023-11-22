`timescale 1ns / 1ps

    module or_by_nand(
        input a0,
        input a1,
        input a2,
        input a3,
        output res
    );
    
    wire not_a0, not_a1, not_a2, not_a3, or_1, or_2, not_or1, not_or2;
    
    nand(not_a0, a0, a0);
    nand(not_a1, a1, a1);
    nand(or_1, not_a0, not_a1);
    nand(not_or1, or_1, or_1);
    
    nand(not_a2, a2, a2);
    nand(not_a3, a3, a3);
    nand(or_2, not_a2, not_a3);
    nand(not_or2, or_2, or_2);
    
    nand(res, not_or1, not_or2);
    
endmodule