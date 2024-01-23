############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project lab2
set_top getFilterOut
add_files lab2/filter.h
add_files lab2/filter.c
add_files -tb lab2/filter_tb.c -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xc7a100t-csg324-1} -tool vivado
create_clock -period 10 -name default
config_export -display_name a_negrash-ip-block -format ip_catalog -rtl verilog -vendor a_negrash -version 0.0.0
#source "./lab2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog -vendor "a_negrash" -version "0.0.0" -display_name "a_negrash-ip-block"
