// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXILiteS
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read)
//         bit 7  - auto_restart (Read/Write)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0  - Channel 0 (ap_done)
//         bit 1  - Channel 1 (ap_ready)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0  - Channel 0 (ap_done)
//         bit 1  - Channel 1 (ap_ready)
//         others - reserved
// 0x080 : Data signal of depth
//         bit 15~0 - depth[15:0] (Read/Write)
//         others   - reserved
// 0x084 : reserved
// 0x100 : Data signal of out_correct
//         bit 0  - out_correct[0] (Read)
//         others - reserved
// 0x104 : Control signal of out_correct
//         bit 0  - out_correct_ap_vld (Read/COR)
//         others - reserved
// 0x040 ~
// 0x07f : Memory 'inputs' (10 * 32b)
//         Word n : bit [31:0] - inputs[n]
// 0x0c0 ~
// 0x0ff : Memory 'out_r' (10 * 32b)
//         Word n : bit [31:0] - out_r[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XGETFILTEROUT_AXILITES_ADDR_AP_CTRL          0x000
#define XGETFILTEROUT_AXILITES_ADDR_GIE              0x004
#define XGETFILTEROUT_AXILITES_ADDR_IER              0x008
#define XGETFILTEROUT_AXILITES_ADDR_ISR              0x00c
#define XGETFILTEROUT_AXILITES_ADDR_DEPTH_DATA       0x080
#define XGETFILTEROUT_AXILITES_BITS_DEPTH_DATA       16
#define XGETFILTEROUT_AXILITES_ADDR_OUT_CORRECT_DATA 0x100
#define XGETFILTEROUT_AXILITES_BITS_OUT_CORRECT_DATA 1
#define XGETFILTEROUT_AXILITES_ADDR_OUT_CORRECT_CTRL 0x104
#define XGETFILTEROUT_AXILITES_ADDR_INPUTS_BASE      0x040
#define XGETFILTEROUT_AXILITES_ADDR_INPUTS_HIGH      0x07f
#define XGETFILTEROUT_AXILITES_WIDTH_INPUTS          32
#define XGETFILTEROUT_AXILITES_DEPTH_INPUTS          10
#define XGETFILTEROUT_AXILITES_ADDR_OUT_R_BASE       0x0c0
#define XGETFILTEROUT_AXILITES_ADDR_OUT_R_HIGH       0x0ff
#define XGETFILTEROUT_AXILITES_WIDTH_OUT_R           32
#define XGETFILTEROUT_AXILITES_DEPTH_OUT_R           10

