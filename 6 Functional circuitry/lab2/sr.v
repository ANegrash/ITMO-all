`timescale 1ns / 1ps

    module sr(
        input clk_i,
        input rst_i,
        input [7:0] a_i,
        input start_i,
        output reg busy_o,
        output reg [3:0] y_bo
    );

    localparam IDLE = 0,
               WORK = 1,
               CHECK_X = 2,
               SUB_B = 3;

    reg signed [15:0] m;
    wire end_step;
    reg [7:0] x;
    reg [31:0] b, y, tmp1;
    reg [4:0] state;

    reg [31:0] sum_a;
    reg [31:0] sum_b;
    wire [31:0] sum_out;

    adder sum_inst(
        .a(sum_a),
        .b(sum_b),
        .out(sum_out)
    );

    assign end_step = (m == 'h0);

    always @(posedge clk_i) begin
        if (rst_i) begin
            y_bo <= 0;
            busy_o <= 0;
            m <= 'd64;
            state <= IDLE;
        end else begin
            case (state)
                IDLE:
                    begin
                        if (start_i) begin
                            y_bo <= 0;
                            state <= WORK;
                            busy_o <= 1;
                            x <= a_i;
                            m <= 'd64;
                            y <= 0;
                        end
                    end
                WORK:
                    begin
                        if (end_step) begin
                            state <= IDLE;
                            busy_o <= 0;
                            y_bo <= y;
                        end else begin
                            b <= y | m;
                            y <= y >> 1;
                            state <= CHECK_X;
                        end
                    end  
                 CHECK_X:
                    begin
                        if (x >= b) begin
                            sum_a = x;
                            sum_b = ~b + 1;
                            state <= SUB_B;
                        end else begin
                            m <= m >> 2;
                            state <= WORK;
                        end
                    end
                  SUB_B: 
                      begin 
                            x = sum_out;
                            y <= y | m;
                            m <= m >> 2;
                            state <= WORK;
                      end
            endcase
        end
    end
endmodule