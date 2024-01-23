`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 15.09.2023 02:13:07
// Design Name: 
// Module Name: dev_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module dev_tb;
    reg [15:0] switches;
    wire [15:0] leds;
    reg reset;
    reg clk;
    reg uart_rx;
    wire uart_tx;
    
    lab1_design_wrapper dut (
        .dip_switches_16bits_tri_i(switches),
        .led_16bits_tri_io(leds),
        .reset(reset),
        .sys_clock(clk),
        .usb_uart_rxd(uart_rx),
        .usb_uart_txd(uart_tx)
    );
    
    always #5 clk<=~clk;
    
    initial begin
        reset = 0;
        uart_rx = 0;
        switches = 16'h0;
        clk = 0;
        #100;
        reset = 1;
    end
endmodule
