vlib work
vlib riviera

vlib riviera/xil_defaultlib
vlib riviera/xpm
vlib riviera/microblaze_v11_0_1
vlib riviera/axi_lite_ipif_v3_0_4
vlib riviera/lib_cdc_v1_0_2
vlib riviera/interrupt_control_v3_1_4
vlib riviera/axi_gpio_v2_0_21
vlib riviera/lib_pkg_v1_0_2
vlib riviera/lib_srl_fifo_v1_0_2
vlib riviera/axi_uartlite_v2_0_23
vlib riviera/lmb_v10_v3_0_9
vlib riviera/lmb_bram_if_cntlr_v4_0_16
vlib riviera/blk_mem_gen_v8_4_3
vlib riviera/mdm_v3_2_16
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/generic_baseblocks_v2_1_0
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_register_slice_v2_1_19
vlib riviera/fifo_generator_v13_2_4
vlib riviera/axi_data_fifo_v2_1_18
vlib riviera/axi_crossbar_v2_1_20
vlib riviera/util_vector_logic_v2_0_1
vlib riviera/xbip_utils_v3_0_10
vlib riviera/axi_utils_v2_0_6
vlib riviera/xbip_pipe_v3_0_6
vlib riviera/xbip_dsp48_wrapper_v3_0_4
vlib riviera/xbip_dsp48_addsub_v3_0_6
vlib riviera/xbip_dsp48_multadd_v3_0_6
vlib riviera/xbip_bram18k_v3_0_6
vlib riviera/mult_gen_v12_0_15
vlib riviera/floating_point_v7_1_8

vmap xil_defaultlib riviera/xil_defaultlib
vmap xpm riviera/xpm
vmap microblaze_v11_0_1 riviera/microblaze_v11_0_1
vmap axi_lite_ipif_v3_0_4 riviera/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 riviera/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_21 riviera/axi_gpio_v2_0_21
vmap lib_pkg_v1_0_2 riviera/lib_pkg_v1_0_2
vmap lib_srl_fifo_v1_0_2 riviera/lib_srl_fifo_v1_0_2
vmap axi_uartlite_v2_0_23 riviera/axi_uartlite_v2_0_23
vmap lmb_v10_v3_0_9 riviera/lmb_v10_v3_0_9
vmap lmb_bram_if_cntlr_v4_0_16 riviera/lmb_bram_if_cntlr_v4_0_16
vmap blk_mem_gen_v8_4_3 riviera/blk_mem_gen_v8_4_3
vmap mdm_v3_2_16 riviera/mdm_v3_2_16
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap generic_baseblocks_v2_1_0 riviera/generic_baseblocks_v2_1_0
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_19 riviera/axi_register_slice_v2_1_19
vmap fifo_generator_v13_2_4 riviera/fifo_generator_v13_2_4
vmap axi_data_fifo_v2_1_18 riviera/axi_data_fifo_v2_1_18
vmap axi_crossbar_v2_1_20 riviera/axi_crossbar_v2_1_20
vmap util_vector_logic_v2_0_1 riviera/util_vector_logic_v2_0_1
vmap xbip_utils_v3_0_10 riviera/xbip_utils_v3_0_10
vmap axi_utils_v2_0_6 riviera/axi_utils_v2_0_6
vmap xbip_pipe_v3_0_6 riviera/xbip_pipe_v3_0_6
vmap xbip_dsp48_wrapper_v3_0_4 riviera/xbip_dsp48_wrapper_v3_0_4
vmap xbip_dsp48_addsub_v3_0_6 riviera/xbip_dsp48_addsub_v3_0_6
vmap xbip_dsp48_multadd_v3_0_6 riviera/xbip_dsp48_multadd_v3_0_6
vmap xbip_bram18k_v3_0_6 riviera/xbip_bram18k_v3_0_6
vmap mult_gen_v12_0_15 riviera/mult_gen_v12_0_15
vmap floating_point_v7_1_8 riviera/floating_point_v7_1_8

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work microblaze_v11_0_1 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/f8c3/hdl/microblaze_v11_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_microblaze_0_0/sim/lab1_design_microblaze_0_0.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_21 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9c6e/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_axi_gpio_0_0/sim/lab1_design_axi_gpio_0_0.vhd" \

vcom -work lib_pkg_v1_0_2 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_uartlite_v2_0_23 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/0315/hdl/axi_uartlite_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_axi_uartlite_0_0/sim/lab1_design_axi_uartlite_0_0.vhd" \

vcom -work lmb_v10_v3_0_9 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/78eb/hdl/lmb_v10_v3_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_dlmb_v10_0/sim/lab1_design_dlmb_v10_0.vhd" \
"../../../bd/lab1_design/ip/lab1_design_ilmb_v10_0/sim/lab1_design_ilmb_v10_0.vhd" \

vcom -work lmb_bram_if_cntlr_v4_0_16 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/6335/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_dlmb_bram_if_cntlr_0/sim/lab1_design_dlmb_bram_if_cntlr_0.vhd" \
"../../../bd/lab1_design/ip/lab1_design_ilmb_bram_if_cntlr_0/sim/lab1_design_ilmb_bram_if_cntlr_0.vhd" \

vlog -work blk_mem_gen_v8_4_3  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c001/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../bd/lab1_design/ip/lab1_design_lmb_bram_0/sim/lab1_design_lmb_bram_0.v" \

vcom -work mdm_v3_2_16 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/550e/hdl/mdm_v3_2_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_mdm_1_0/sim/lab1_design_mdm_1_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../bd/lab1_design/ip/lab1_design_clk_wiz_1_0/lab1_design_clk_wiz_1_0_clk_wiz.v" \
"../../../bd/lab1_design/ip/lab1_design_clk_wiz_1_0/lab1_design_clk_wiz_1_0.v" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/lab1_design/ip/lab1_design_rst_clk_wiz_1_100M_0/sim/lab1_design_rst_clk_wiz_1_100M_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_19  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/4d88/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_4  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/1f5a/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_4 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/1f5a/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_4  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/1f5a/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_18  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/5b9c/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_20  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ace7/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../bd/lab1_design/ip/lab1_design_xbar_0/sim/lab1_design_xbar_0.v" \

vlog -work util_vector_logic_v2_0_1  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/2137/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../bd/lab1_design/ip/lab1_design_reset_inv_0_0/sim/lab1_design_reset_inv_0_0.v" \

vcom -work xbip_utils_v3_0_10 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/1123/hdl/xbip_utils_v3_0_vh_rfs.vhd" \

vcom -work axi_utils_v2_0_6 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/1971/hdl/axi_utils_v2_0_vh_rfs.vhd" \

vcom -work xbip_pipe_v3_0_6 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/7468/hdl/xbip_pipe_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_wrapper_v3_0_4 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/cdbf/hdl/xbip_dsp48_wrapper_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_addsub_v3_0_6 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/910d/hdl/xbip_dsp48_addsub_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_multadd_v3_0_6 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/b0ac/hdl/xbip_dsp48_multadd_v3_0_vh_rfs.vhd" \

vcom -work xbip_bram18k_v3_0_6 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/d367/hdl/xbip_bram18k_v3_0_vh_rfs.vhd" \

vcom -work mult_gen_v12_0_15 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/d4d2/hdl/mult_gen_v12_0_vh_rfs.vhd" \

vcom -work floating_point_v7_1_8 -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/83a3/hdl/floating_point_v7_1_vh_rfs.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut_AXILiteS_s_axi.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut_faddbkb.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut_fdivdEe.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut_fmulcud.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut_sitoeOg.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/p_hls_fptosi_float_i.v" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/verilog/getFilterOut.v" \

vcom -work xil_defaultlib -93 \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/ip/getFilterOut_ap_fadd_3_full_dsp_32.vhd" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/ip/getFilterOut_ap_fdiv_14_no_dsp_32.vhd" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/ip/getFilterOut_ap_fmul_2_max_dsp_32.vhd" \
"../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/9fe6/hdl/ip/getFilterOut_ap_sitofp_4_no_dsp_32.vhd" \
"../../../bd/lab1_design/ip/lab1_design_getFilterOut_0_2/sim/lab1_design_getFilterOut_0_2.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/c923" "+incdir+../../../../lab3.srcs/sources_1/bd/lab1_design/ipshared/ec67/hdl" \
"../../../bd/lab1_design/sim/lab1_design.v" \

vlog -work xil_defaultlib \
"glbl.v"

