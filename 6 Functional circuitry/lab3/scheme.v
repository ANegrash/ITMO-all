`timescale 1ns / 1ps

    module shema(
        input clk_i,
        input rst_i,
      
        input [7:0] a,
        input [7:0] b,
        input start_i,
        
        output reg [7:0] AN,
        output wire [6:0] led,
        output reg zero,
        output busy
    );
    
    wire [0:15] y;
    fun fun(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .a_i(a),
        .b_i(b),
        .start_i(start_i),
        .busy_o(busy),
        .y_bo(y)
    );
    
    wire clk_o;
    freq_div(
        .clk_in(clk_i),
        .clk_out(clk_o)
    );
    
    reg [3:0] x;
    reg [3:0] cnt;
    
    seg_led_7 seg(
        .x(x),
        .digit(led)
    );
    
    always @(posedge clk_o) begin
        zero <= 1;
        case(cnt)
            0: begin
                AN <= 8'b11110111;
                x <= (y / 1000) % 10;
            end
            1: begin
                AN <= 8'b11111011;
                x <= (y / 100) % 10;
            end
            2: begin
                AN <= 8'b11111101;
                x <= (y / 10) % 10;
            end
            3: begin
                AN <= 8'b11111110;
                x <= y % 10;
            end
        endcase
        
        if (cnt >= 3) begin 
            cnt <= 0;
        end else begin
            cnt <= cnt + 1;
        end                      
    end
endmodule