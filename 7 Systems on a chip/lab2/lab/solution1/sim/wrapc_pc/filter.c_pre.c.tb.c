// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "E:/SoC/lab2/filter.c"
# 1 "E:/SoC/lab2/filter.c" 1
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 147 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "E:/SoC/lab2/filter.c" 2
# 1 "E:/SoC/lab2/filter.h" 1


# 1 "C:/Xilinx/Vivado/2019.1/win64/tools/clang/bin/../lib/clang/3.1/include\\stdbool.h" 1 3 4
# 4 "E:/SoC/lab2/filter.h" 2




void getFilterOut (
  int inputs[10],
  unsigned short depth,
  int out[10],
  _Bool* out_correct
  );
# 2 "E:/SoC/lab2/filter.c" 2



void getFilterOut (
  int inputs[10],
  unsigned short depth,
  int out[10],
  _Bool* out_correct
  ) {






 if (depth < 3 || depth > 10) {
  out_correct = 0;
  return;
 }
 float coef = 1.0f / (depth + 1);
 OuterLoop: for (int i = 0; i < 10; ++i) {
#pragma HLS UNROLL
 float sum = 0;
  InnerLoop: for (int j = i - depth; j < i; ++j) {
#pragma HLS UNROLL
 if (j >= 0)
    sum += inputs[j];
  }
  out[i] = (int)(sum * coef);
 }
 *out_correct = 1;
 return;
}
