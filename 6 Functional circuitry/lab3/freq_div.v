`timescale 1ns / 1ps

    module freq_div(
        input clk_in,
        output reg clk_out
    );

    reg[27:0] c = 28'd0;
    parameter DIVISOR = 28'd50000;

    always @(posedge clk_in) begin
         c <= c + 28'd1;
         if (c >= (DIVISOR - 1)) begin
            c <= 28'd0;
         end
         clk_out <= (c < DIVISOR / 2) ? 1'b1 : 1'b0;
    end
endmodule