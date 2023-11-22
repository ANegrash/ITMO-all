`timescale 1ns / 1ps

    module fun(
        input clk_i,
        input rst_i,
        input [7:0] a_i,
        input [7:0] b_i,
        input start_i,
        output reg busy_o,
        output reg [11:0] y_bo
    );

    localparam IDLE = 0,
               MUL = 1,
               WAIT_MUL = 2,
               SR = 3,
               WAIT_SR = 4,
               WAIT_SUM = 5;
           
    reg [3:0] state = IDLE;

    reg [7:0] mult2_a;
    reg [7:0] mult2_b;
    wire [15:0] mult2_y;
    reg mult2_start;
    wire mult2_busy;

    mul mul2_inst(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .a_bi(mult2_a),
        .b_bi(mult2_b),
        .start_i(mult2_start),
        .busy_o(mult2_busy),
        .y_bo(mult2_y)
    );

    reg start_sr;
    reg [7:0] in_sr;
    wire [3:0] out_sr;
    wire busy_sr;

    sr sr_inst(
        .clk_i(clk_i),
        .rst_i(rst_i),
        .a_i(in_sr),
        .start_i(start_sr),
        .y_bo(out_sr),
        .busy_o(busy_sr)
    );
 
    always @(posedge clk_i) begin
        if (rst_i) begin
            y_bo <= 0;
            busy_o <= 0;
            start_sr <= 0;
            mult2_start <= 0;
            state <= IDLE;
        end else begin
            case (state)
                IDLE:
                    begin
                        if (start_i) begin
                            y_bo <= 0;
                            busy_o <= 1;
                            state <= SR;
                        end
                    end
                SR:
                    begin
                        in_sr <= b_i;
                        start_sr <= 1;
                        state <= WAIT_SR;
                    end
                WAIT_SR:
                    begin
                        start_sr <= 0;
                        if (~busy_sr && ~start_sr) begin
                            mult2_a <= a_i; 
                            mult2_b <= out_sr;
                            mult2_start <= 1;
                            state <= WAIT_MUL;
                        end
                    end
                WAIT_MUL:
                    begin
                        mult2_start <= 0;
                        if (~mult2_busy && ~mult2_start) begin
                            y_bo <= mult2_y;
                            busy_o <= 0;
                            state <= IDLE;
                        end
                    end
            endcase
        end
    end
endmodule