/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdbool.h>
#include <stdio.h>
#include "platform.h"
#include "sleep.h"
#include "xil_printf.h"
#include "xil_io.h"

#define MAX_DEPTH 10

#define SIM_RUN

#define AXEL_CTRL        0x44a00000
#define AXEL_INPUTS      0x44a00040
#define AXEL_DEPTH       0x44a00080
#define AXEL_OUTPUTS     0x44a000c0
#define AXEL_OUT_CORRECT 0x44a00100

static unsigned short filterDepth = MAX_DEPTH;
static float filterCoef = 1.0f / (MAX_DEPTH + 1);
static int data[MAX_DEPTH] = {0, 1, 2, 3, 4000, -5452, 6, 7, 8000, 9000};
static int out[MAX_DEPTH];

static void update_filter_params(const unsigned short newDepth) {
	if (newDepth >= 3 && newDepth <= MAX_DEPTH) {
		filterDepth = newDepth;
		filterCoef = 1.0f / (newDepth + 1);
	}
#ifndef SIM_RUN
	printf("New filter param: %d\n", filterDepth);
	printf("coef: %f\n", filterCoef);
#endif
}

static bool is_series_entered() {
	unsigned int sw = Xil_In16(0x40000008);
	return !(sw & 1);
}

static int getFilterOut(unsigned short start_index) {
	float sum = 0;
	for (int i = start_index - filterDepth; i < start_index; ++i) {
		if (i >= 0)
			sum += data[i];
	}
	return (int)((float)sum * filterCoef);
}

static void calculateFilter(int data[MAX_DEPTH], unsigned short depth, int* result, bool useAxel, bool *outCorrect) {
	if (!useAxel) {
		if (depth < 3 || depth > MAX_DEPTH) {
			*outCorrect = false;
			return;
		}
		update_filter_params(depth);
		for (int i = 0; i < MAX_DEPTH; ++i) {
			result[i] = getFilterOut(i);
		}
		*outCorrect = true;
	}
	else {
		for (int i = 0; i < MAX_DEPTH; ++i) {
			Xil_Out32(AXEL_INPUTS + 4 * i, data[i]);
		}
		Xil_Out32(AXEL_DEPTH, depth);
		Xil_Out8(AXEL_CTRL, 1);
		while((Xil_In8(AXEL_CTRL) & 0x2) != 0x2);
		*outCorrect = Xil_In8(AXEL_OUT_CORRECT);
		for (int i = 0; i < MAX_DEPTH; ++i) {
			result[i] = Xil_In32(AXEL_OUTPUTS + 4 * i);
		}
	}
}

int main() {
	int depth = 3;
	bool outCorrect;
	Xil_Out16(0x40000004, 0);
	Xil_Out16(0x4000000c, 1);
	for (depth = 3; depth <= MAX_DEPTH; ++depth) {
		Xil_Out16(0x40000000, 0x41);
		Xil_Out16(0x40000000, 0);
		calculateFilter(data, depth, out, true,&outCorrect);
		Xil_Out16(0x40000000, 42);
		Xil_Out16(0x40000000, 0);
		for (int i = 0; i < MAX_DEPTH; ++i) {
			Xil_Out16(0x40000000, out[i]);
			Xil_Out16(0x40000000, 0);
		}
		Xil_Out16(0x40000000, 0x43);
		Xil_Out16(0x40000000, 0);
	}
    return 0;
}
