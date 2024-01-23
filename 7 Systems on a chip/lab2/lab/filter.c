#include "filter.h"

#include <stdbool.h>

void getFilterOut (
		int inputs[MAX_DEPTH], //actually input
		unsigned short depth,  //actually input
		int out[MAX_DEPTH],  //actually output
		bool* out_correct       //actually output
		) {
// needed for lab3
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=out_correct
#pragma HLS INTERFACE s_axilite port=out
#pragma HLS INTERFACE s_axilite port=depth
#pragma HLS INTERFACE s_axilite port=inputs
	if (depth < 3 || depth > MAX_DEPTH) {
		out_correct = false;
		return;
	}
	float coef = 1.0f / (depth + 1);
	OuterLoop: for (int i = 0; i < MAX_DEPTH; ++i) {
#pragma HLS UNROLL
		float sum = 0;
		InnerLoop: for (int j = i - depth; j < i; ++j) {
#pragma HLS PIPELINE
			if (j >= 0)
				sum += inputs[j];
		}
		out[i] = (int)(sum * coef);
	}
	*out_correct = true;
	return;
}
