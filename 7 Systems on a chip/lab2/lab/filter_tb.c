#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "filter.h"

#define SEED 100
#define SAMPLES 5

bool golden_getFilterResult(int inputs[MAX_DEPTH], unsigned short depth, int res[MAX_DEPTH]) {
	if (depth < 3 || depth > MAX_DEPTH) return false;
	float coef = 1.0f / (depth + 1);
	for (int i = 0; i < MAX_DEPTH; ++i) {
		float sum = 0;
		for (int j = i - depth; j < i; ++j) {
			if (j >= 0)
				sum += inputs[j];
		}
		res[i] = (int)(sum * coef);
	}
	return true;
}

bool float_eq(float tolerance, float a, float b) {
	return abs(a-b) < tolerance;
}

int main() {
	srand(SEED);
	for (size_t i = 0; i < SAMPLES; ++i) {
		int inputs[MAX_DEPTH];
		int golden_out[MAX_DEPTH];
		int dut_out[MAX_DEPTH];
		int test_depth = rand() % 13;
		size_t j;
		for (j = 0; j < MAX_DEPTH; ++j) {
			inputs[j] = rand();
		}

		bool dut_success = false;
		bool golden_success = golden_getFilterResult(inputs, test_depth, golden_out);

		getFilterOut(inputs, test_depth, dut_out, &dut_success);

		if (golden_success != dut_success) {
			printf("TEST FAILED! Wrong success!\n");
			printf("Iteration: %zu\n", i);
			printf("Golden success: %d\n", golden_success);
			printf("DUT success: %d\n", dut_success);
			return 1;
		}

		if (!golden_success) continue;

		for (j = 0; j < MAX_DEPTH; ++j) {
			if (!float_eq(10e-6, dut_out[j], golden_out[j])) {
				printf("TEST FAILED! Wrong answer!\n");
				printf("Iteration: %zu\n", i);
				printf("Position: %zu\n", j);
				printf("Golden out: %d\n", golden_out[j]);
				printf("DUT out: %d\n", dut_out[j]);
				return 1;
			}
		}
	}
	printf("PASSED!\n");
}
