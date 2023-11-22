`timescale 1ns / 1ps

module shifrator_tb;
    reg [7:0] inputs;
    wire q_1, q_2, q_4;
    
    shifrator shifrator_1(
        .a(inputs),
        .q1(q_1),
        .q2(q_2),
        .q4(q_4)
    );
    
    integer i, c;
    reg [7:0] test_val;
    reg [2:0] expected_val;
    
    initial begin
        for (i = 0; i < 8; i = i+1) begin
            c = $pow(2, i);
            test_val = c;
            inputs = test_val;
            expected_val = i;
            #10
            if (q_1 == expected_val[0] && q_2 == expected_val[1] && q_4 == expected_val[2]) begin
                $display ("Correct for %b: q4=%b, q2=%b, q1=%b", c, q_4, q_2, q_1);
            end else begin
                $display ("Wrong for %b: q4=%b, q2=%b, q1=%b", c, q_4, q_2, q_1);
            end
        end
        #10 $stop;
    end

endmodule