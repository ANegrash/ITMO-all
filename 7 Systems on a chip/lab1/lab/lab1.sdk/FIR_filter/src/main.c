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

//#define SIMULATION_RUN

static unsigned short filterDepth = MAX_DEPTH;
static float filterCoef = 1.0f / (MAX_DEPTH + 1);
static int data[MAX_DEPTH] = {0, 1, 2, 3, 4000, -5452, 6, 7, 8000, 9000};

static void update_filter_params(const unsigned short newDepth) {
	if (newDepth > 3 && newDepth <= MAX_DEPTH) {
		filterDepth = newDepth;
		filterCoef = 1.0f / (newDepth + 1);
	}
#ifndef SIMULATION_RUN
	printf("New filter param: %d\n", filterDepth);
	printf("coef: %f\n", filterCoef);
#endif
}

static int getFilterOut(unsigned short start_index) {
	float sum = 0;
	for (int i = start_index - filterDepth; i < start_index; ++i) {
		if (i >= 0)
			sum += data[i];
	}
	return (int)((float)sum * filterCoef);
}

static bool is_series_entered() {
	unsigned int sw = Xil_In16(0x40000008);
	return !(sw & 1);
}

int main() {
	Xil_Out16(0x40000004, 0);
	Xil_Out16(0x4000000c, 1);
#ifndef SIMULATION_RUN
	printf("Hello, World!\n");
	Xil_Out16(0x40000000, 1);
	sleep(1);
	Xil_Out16(0x40000000, 2);
	sleep(1);
	Xil_Out16(0x40000000, 4);
	sleep(1);
	Xil_Out16(0x40000000, 0);
#else
	update_filter_params(10);
#endif
    while(true) {
#ifndef SIMULATION_RUN
    	if (is_series_entered()) {
    		unsigned int p;
            printf("Please input filter param:\n");
            scanf("%d", &p);
            printf("\n");
            update_filter_params(p);
            printf("Move switch to proceed to series input\n");
            while(is_series_entered());
    	}
    	printf("Enter series of 10 values\n");
    	for (unsigned short i = 0; i < 10; ++i) {
    	    scanf("%d", data+i);
    	    printf("%d ", data[i]);
    	}
    	printf("\n");
#endif
    	for (int i = 0; i < MAX_DEPTH; ++i) {
    		int out = getFilterOut(i);
    		Xil_Out16(0x40000000, out);
#ifndef SIMULATION_RUN
    	    printf("Filter out %u: %d\n", i, out);
    	    sleep(1);
#endif
    	    Xil_Out16(0x40000000, 1);
    	}
#ifdef SIMULATION_RUN
    	break;
#endif
    }
    return 0;
}
