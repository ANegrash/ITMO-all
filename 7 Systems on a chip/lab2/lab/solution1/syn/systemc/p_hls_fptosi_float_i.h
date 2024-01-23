// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _p_hls_fptosi_float_i_HH_
#define _p_hls_fptosi_float_i_HH_

#include "systemc.h"
#include "AESL_pkg.h"


namespace ap_rtl {

struct p_hls_fptosi_float_i : public sc_module {
    // Port declarations 8
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_in< sc_lv<32> > x;
    sc_out< sc_lv<32> > ap_return;


    // Module declarations
    p_hls_fptosi_float_i(sc_module_name name);
    SC_HAS_PROCESS(p_hls_fptosi_float_i);

    ~p_hls_fptosi_float_i();

    sc_trace_file* mVcdFile;

    sc_signal< sc_lv<2> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_lv<1> > p_Result_s_reg_185;
    sc_signal< sc_lv<32> > p_Val2_5_fu_166_p3;
    sc_signal< sc_lv<32> > p_Val2_5_reg_190;
    sc_signal< sc_lv<32> > p_Val2_s_fu_44_p1;
    sc_signal< sc_lv<23> > tmp_V_1_fu_66_p1;
    sc_signal< sc_lv<25> > mantissa_V_fu_70_p4;
    sc_signal< sc_lv<8> > tmp_V_fu_56_p4;
    sc_signal< sc_lv<9> > zext_ln339_fu_84_p1;
    sc_signal< sc_lv<9> > add_ln339_fu_88_p2;
    sc_signal< sc_lv<8> > sub_ln1311_fu_102_p2;
    sc_signal< sc_lv<1> > isNeg_fu_94_p3;
    sc_signal< sc_lv<9> > sext_ln1311_fu_108_p1;
    sc_signal< sc_lv<9> > ush_fu_112_p3;
    sc_signal< sc_lv<32> > sext_ln1311_1_fu_120_p1;
    sc_signal< sc_lv<25> > sext_ln1311_2_fu_124_p1;
    sc_signal< sc_lv<79> > zext_ln682_fu_80_p1;
    sc_signal< sc_lv<79> > zext_ln1287_fu_128_p1;
    sc_signal< sc_lv<25> > r_V_fu_132_p2;
    sc_signal< sc_lv<1> > tmp_fu_144_p3;
    sc_signal< sc_lv<79> > r_V_1_fu_138_p2;
    sc_signal< sc_lv<32> > zext_ln662_fu_152_p1;
    sc_signal< sc_lv<32> > tmp_1_fu_156_p4;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<32> > result_V_1_fu_174_p2;
    sc_signal< sc_lv<2> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<2> ap_ST_fsm_state1;
    static const sc_lv<2> ap_ST_fsm_state2;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1F;
    static const sc_lv<32> ap_const_lv32_17;
    static const sc_lv<32> ap_const_lv32_1E;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<9> ap_const_lv9_181;
    static const sc_lv<32> ap_const_lv32_8;
    static const sc_lv<8> ap_const_lv8_7F;
    static const sc_lv<32> ap_const_lv32_18;
    static const sc_lv<32> ap_const_lv32_37;
    static const sc_lv<32> ap_const_lv32_1;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_add_ln339_fu_88_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_ap_return();
    void thread_isNeg_fu_94_p3();
    void thread_mantissa_V_fu_70_p4();
    void thread_p_Val2_5_fu_166_p3();
    void thread_p_Val2_s_fu_44_p1();
    void thread_r_V_1_fu_138_p2();
    void thread_r_V_fu_132_p2();
    void thread_result_V_1_fu_174_p2();
    void thread_sext_ln1311_1_fu_120_p1();
    void thread_sext_ln1311_2_fu_124_p1();
    void thread_sext_ln1311_fu_108_p1();
    void thread_sub_ln1311_fu_102_p2();
    void thread_tmp_1_fu_156_p4();
    void thread_tmp_V_1_fu_66_p1();
    void thread_tmp_V_fu_56_p4();
    void thread_tmp_fu_144_p3();
    void thread_ush_fu_112_p3();
    void thread_zext_ln1287_fu_128_p1();
    void thread_zext_ln339_fu_84_p1();
    void thread_zext_ln662_fu_152_p1();
    void thread_zext_ln682_fu_80_p1();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif
