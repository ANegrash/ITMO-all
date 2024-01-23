// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;


// [dump_struct_tree [build_nameSpaceTree] dumpedStructList] ---------->


// [dump_enumeration [get_enumeration_list]] ---------->


// wrapc file define: "inputs"
#define AUTOTB_TVIN_inputs  "../tv/cdatafile/c.getFilterOut.autotvin_inputs.dat"
// wrapc file define: "depth"
#define AUTOTB_TVIN_depth  "../tv/cdatafile/c.getFilterOut.autotvin_depth.dat"
// wrapc file define: "out_r"
#define AUTOTB_TVOUT_out_r  "../tv/cdatafile/c.getFilterOut.autotvout_out_r.dat"
#define AUTOTB_TVIN_out_r  "../tv/cdatafile/c.getFilterOut.autotvin_out_r.dat"
// wrapc file define: "out_correct"
#define AUTOTB_TVOUT_out_correct  "../tv/cdatafile/c.getFilterOut.autotvout_out_correct.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "out_r"
#define AUTOTB_TVOUT_PC_out_r  "../tv/rtldatafile/rtl.getFilterOut.autotvout_out_r.dat"
// tvout file define: "out_correct"
#define AUTOTB_TVOUT_PC_out_correct  "../tv/rtldatafile/rtl.getFilterOut.autotvout_out_correct.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			inputs_depth = 0;
			depth_depth = 0;
			out_r_depth = 0;
			out_correct_depth = 0;
			trans_num =0;
		}

		~INTER_TCL_FILE() {
			mFile.open(mName);
			if (!mFile.good()) {
				cout << "Failed to open file ref.tcl" << endl;
				exit (1);
			}
			string total_list = get_depth_list();
			mFile << "set depth_list {\n";
			mFile << total_list;
			mFile << "}\n";
			mFile << "set trans_num "<<trans_num<<endl;
			mFile.close();
		}

		string get_depth_list () {
			stringstream total_list;
			total_list << "{inputs " << inputs_depth << "}\n";
			total_list << "{depth " << depth_depth << "}\n";
			total_list << "{out_r " << out_r_depth << "}\n";
			total_list << "{out_correct " << out_correct_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int inputs_depth;
		int depth_depth;
		int out_r_depth;
		int out_correct_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern "C" void getFilterOut (
int inputs[10],
short depth,
int out[10],
_Bool* out_correct);

extern "C" void AESL_WRAP_getFilterOut (
int inputs[10],
short depth,
int out[10],
_Bool* out_correct)
{
	refine_signal_handler();
	fstream wrapc_switch_file_token;
	wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
	int AESL_i;
	if (wrapc_switch_file_token.good())
	{
		CodeState = ENTER_WRAPC_PC;
		static unsigned AESL_transaction_pc = 0;
		string AESL_token;
		string AESL_num;
		static AESL_FILE_HANDLER aesl_fh;


		// output port post check: "out_r"
		aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // data

			sc_bv<32> *out_r_pc_buffer = new sc_bv<32>[10];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_r', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_r', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					out_r_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_out_r))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: out_r
				{
					// bitslice(31, 0)
					// {
						// celement: out(31, 0)
						// {
							sc_lv<32>* out_lv0_0_9_1 = new sc_lv<32>[10];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out(31, 0)
						{
							// carray: (0) => (9) @ (1)
							for (int i_0 = 0; i_0 <= 9; i_0 += 1)
							{
								if (&(out[0]) != NULL) // check the null address if the c port is array or others
								{
									out_lv0_0_9_1[hls_map_index].range(31, 0) = sc_bv<32>(out_r_pc_buffer[hls_map_index].range(31, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out(31, 0)
						{
							// carray: (0) => (9) @ (1)
							for (int i_0 = 0; i_0 <= 9; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : out[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : out[0]
								// output_left_conversion : out[i_0]
								// output_type_conversion : (out_lv0_0_9_1[hls_map_index]).to_uint64()
								if (&(out[0]) != NULL) // check the null address if the c port is array or others
								{
									out[i_0] = (out_lv0_0_9_1[hls_map_index]).to_uint64();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] out_r_pc_buffer;
		}

		// output port post check: "out_correct"
		aesl_fh.read(AUTOTB_TVOUT_PC_out_correct, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_out_correct, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_out_correct, AESL_token); // data

			sc_bv<1> *out_correct_pc_buffer = new sc_bv<1>[1];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_correct', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_correct', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					out_correct_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_out_correct, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_out_correct))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: out_correct
				{
					// bitslice(0, 0)
					// {
						// celement: out_correct(0, 0)
						// {
							sc_lv<1>* out_correct_lv0_0_0_1 = new sc_lv<1>[1];
						// }
					// }

					// bitslice(0, 0)
					{
						int hls_map_index = 0;
						// celement: out_correct(0, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								if (&(out_correct[0]) != NULL) // check the null address if the c port is array or others
								{
									out_correct_lv0_0_0_1[hls_map_index].range(0, 0) = sc_bv<1>(out_correct_pc_buffer[hls_map_index].range(0, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(0, 0)
					{
						int hls_map_index = 0;
						// celement: out_correct(0, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : out_correct[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : out_correct[0]
								// output_left_conversion : out_correct[i_0]
								// output_type_conversion : (out_correct_lv0_0_0_1[hls_map_index]).to_uint64()
								if (&(out_correct[0]) != NULL) // check the null address if the c port is array or others
								{
									out_correct[i_0] = (out_correct_lv0_0_0_1[hls_map_index]).to_uint64();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] out_correct_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "inputs"
		char* tvin_inputs = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_inputs);

		// "depth"
		char* tvin_depth = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_depth);

		// "out_r"
		char* tvin_out_r = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_out_r);
		char* tvout_out_r = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_out_r);

		// "out_correct"
		char* tvout_out_correct = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_out_correct);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_inputs, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_inputs, tvin_inputs);

		sc_bv<32>* inputs_tvin_wrapc_buffer = new sc_bv<32>[10];

		// RTL Name: inputs
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: inputs(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : inputs[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : inputs[0]
						// regulate_c_name       : inputs
						// input_type_conversion : inputs[i_0]
						if (&(inputs[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> inputs_tmp_mem;
							inputs_tmp_mem = inputs[i_0];
							inputs_tvin_wrapc_buffer[hls_map_index].range(31, 0) = inputs_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 10; i++)
		{
			sprintf(tvin_inputs, "%s\n", (inputs_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_inputs, tvin_inputs);
		}

		tcl_file.set_num(10, &tcl_file.inputs_depth);
		sprintf(tvin_inputs, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_inputs, tvin_inputs);

		// release memory allocation
		delete [] inputs_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_depth, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_depth, tvin_depth);

		sc_bv<16> depth_tvin_wrapc_buffer;

		// RTL Name: depth
		{
			// bitslice(15, 0)
			{
				// celement: depth(15, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : depth
						// sub_1st_elem          : 
						// ori_name_1st_elem     : depth
						// regulate_c_name       : depth
						// input_type_conversion : depth
						if (&(depth) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<16> depth_tmp_mem;
							depth_tmp_mem = depth;
							depth_tvin_wrapc_buffer.range(15, 0) = depth_tmp_mem.range(15, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_depth, "%s\n", (depth_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_depth, tvin_depth);
		}

		tcl_file.set_num(1, &tcl_file.depth_depth);
		sprintf(tvin_depth, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_depth, tvin_depth);

		// [[transaction]]
		sprintf(tvin_out_r, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);

		sc_bv<32>* out_r_tvin_wrapc_buffer = new sc_bv<32>[10];

		// RTL Name: out_r
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: out(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : out[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : out[0]
						// regulate_c_name       : out
						// input_type_conversion : out[i_0]
						if (&(out[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> out_tmp_mem;
							out_tmp_mem = out[i_0];
							out_r_tvin_wrapc_buffer[hls_map_index].range(31, 0) = out_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 10; i++)
		{
			sprintf(tvin_out_r, "%s\n", (out_r_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);
		}

		tcl_file.set_num(10, &tcl_file.out_r_depth);
		sprintf(tvin_out_r, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);

		// release memory allocation
		delete [] out_r_tvin_wrapc_buffer;

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		getFilterOut(inputs, depth, out, out_correct);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_out_r, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);

		sc_bv<32>* out_r_tvout_wrapc_buffer = new sc_bv<32>[10];

		// RTL Name: out_r
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: out(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : out[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : out[0]
						// regulate_c_name       : out
						// input_type_conversion : out[i_0]
						if (&(out[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> out_tmp_mem;
							out_tmp_mem = out[i_0];
							out_r_tvout_wrapc_buffer[hls_map_index].range(31, 0) = out_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 10; i++)
		{
			sprintf(tvout_out_r, "%s\n", (out_r_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);
		}

		tcl_file.set_num(10, &tcl_file.out_r_depth);
		sprintf(tvout_out_r, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);

		// release memory allocation
		delete [] out_r_tvout_wrapc_buffer;

		// [[transaction]]
		sprintf(tvout_out_correct, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_out_correct, tvout_out_correct);

		sc_bv<1>* out_correct_tvout_wrapc_buffer = new sc_bv<1>[1];

		// RTL Name: out_correct
		{
			// bitslice(0, 0)
			{
				int hls_map_index = 0;
				// celement: out_correct(0, 0)
				{
					// carray: (0) => (0) @ (1)
					for (int i_0 = 0; i_0 <= 0; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : out_correct[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : out_correct[0]
						// regulate_c_name       : out_correct
						// input_type_conversion : out_correct[i_0]
						if (&(out_correct[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<1> out_correct_tmp_mem;
							out_correct_tmp_mem = out_correct[i_0];
							out_correct_tvout_wrapc_buffer[hls_map_index].range(0, 0) = out_correct_tmp_mem.range(0, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvout_out_correct, "%s\n", (out_correct_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_out_correct, tvout_out_correct);
		}

		tcl_file.set_num(1, &tcl_file.out_correct_depth);
		sprintf(tvout_out_correct, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_out_correct, tvout_out_correct);

		// release memory allocation
		delete [] out_correct_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "inputs"
		delete [] tvin_inputs;
		// release memory allocation: "depth"
		delete [] tvin_depth;
		// release memory allocation: "out_r"
		delete [] tvout_out_r;
		delete [] tvin_out_r;
		// release memory allocation: "out_correct"
		delete [] tvout_out_correct;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

