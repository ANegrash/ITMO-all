    module seg_led_7(
        input wire [3:0] x,
        output reg [0:6] digit
    );

    always @ (*) begin
        case(x)
            4'd0 : digit =7'b0000001;
            4'd1 : digit =7'b1001111;
            4'd2 : digit =7'b0010010;
            4'd3 : digit =7'b0000110;
            4'd4 : digit =7'b1001100;
            4'd5 : digit =7'b0100100;
            4'd6 : digit =7'b0100000;
            4'd7 : digit =7'b0001111;
            4'd8 : digit =7'b0000000;
            4'd9 : digit =7'b0000100;
            4'd10 : digit =7'b0001000;
            4'd11 : digit =7'b1100000;
            4'd12 : digit =7'b0110001;
            4'd13 : digit =7'b1000010;
            4'd14 : digit =7'b0110000;
            4'd15 : digit =7'b0111000;
            default: digit = 7'b1111111;
        endcase
    end
endmodule