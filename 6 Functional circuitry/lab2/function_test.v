`timescale 1ns / 1ps

module fun_test;
    reg clk_reg, start, in_rst;
    reg [7:0] in_a;
    reg [7:0] in_b;
    wire [11:0] out;
    wire out_busy;
    reg [3:0] count;
    integer i, j, expected, count_failed;

    fun ab_inst(
        .clk_i(clk_reg),
        .rst_i(in_rst),
        .a_i(in_a),
        .b_i(in_b),
        .start_i(start),
        .y_bo(out),
        .busy_o(out_busy)
    );

    initial begin
        clk_reg = 1;
        forever
            #1
            clk_reg = ~clk_reg;
    end

    initial begin
        in_rst = 'd1;
        start = 'd0;
        count = 'd0;
        #1
        in_rst = 'd0;
        count_failed = 0;
        
        for (i = 0; i <= 255; i = i+1) begin
            for (j = 0; j <= 255; j = j+1) begin
                in_a = i;
                in_b = j;
                start = 1;
                @(negedge out_busy);
                start = 0;
                expected = i * $floor($sqrt(j));
                if (expected == out) begin
                    $display("Correct! a= %d, b=%d, y=%d", in_a, in_b, out);
                end else begin
                    $display("Wrong((( a= %d, b=%d, y=%d", in_a, in_b, out);
                    count_failed = count_failed + 1;
                end
            end
        end
        
        if (count_failed == 0) begin
            $display("All tests passed successfully!");
        end else begin
            $display("Testing is not completed. Find %d failed test(s).", count_failed);
        end
    end
endmodule
