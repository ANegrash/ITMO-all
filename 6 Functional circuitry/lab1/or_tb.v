`timescale 1ns / 1ps

    module or_tb;
    reg a_0, a_1, a_2, a_3;
    wire c_out;
    
    or_by_nand or_by_nand_1 (
        .a0(a_0),
        .a1(a_1),
        .a2(a_2),
        .a3(a_3),
        .res(c_out)
    );
    
    integer i;
    reg [3:0] test_val;
    reg expected_val;
    
    initial begin
        for (i = 0; i < 16; i = i+1) begin 
            test_val = i;
            a_0 = test_val[0];
            a_1 = test_val[1];
            a_2 = test_val[2];
            a_3 = test_val[3];
            expected_val = |test_val;
            #10

            if (c_out == expected_val) begin
                $display ("Correct!!! a_0=%b, a_1=%b, a_2=%b, a_3=%b, res=%b", a_0, a_1, a_2, a_3, c_out);
            end else begin
                $display ("Wrong!!! a_0=%b, a_1=%b, a_2=%b, a_3=%b, res=%b, expected=%b", a_0, a_1, a_2, a_3, c_out, expected_val);
            end
        end
        #10 $stop;
    end

endmodule