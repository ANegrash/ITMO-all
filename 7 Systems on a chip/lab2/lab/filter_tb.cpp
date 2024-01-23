#include <cstdlib>
#include <cmath>
#include <iostream>

#include "filter.h"


constexpr int SEED = 100;
constexpr size_t SAMPLES = 600;

bool golden_getFilterResult(int (&inputs)[MAX_DEPTH], int depth, float (&res)[MAX_DEPTH]) {
	if (depth < 3 || depth > MAX_DEPTH) return false;
	float coef = 1.0f / (depth + 1);
	for (int i = 0; i < MAX_DEPTH; ++i) {
		float sum = 0;
		for (int j = i - depth; j < i; ++j) {
			if (j > 0)
				sum += inputs[j];
		}
		res[i] = sum * coef;
	}
	return true;
}

bool float_eq(float tolerance, float a, float b) {
	return std::abs(a-b) < tolerance;
}

int main() {
	std::srand(SEED);
	for (size_t i = 0; i < SAMPLES; ++i) {
		int inputs[MAX_DEPTH];
		float golden_out[MAX_DEPTH];
		float dut_out[MAX_DEPTH];
		int test_depth = rand() % 13;
		for (size_t j = 0; j < MAX_DEPTH; ++j) {
			inputs[j] = rand();
		}

		bool dut_success = false;
		bool golden_success = golden_getFilterResult(inputs, test_depth, golden_out);

		getFilterOut(inputs, test_depth, dut_out, &dut_success);

		if (golden_success != dut_success) {
			std::cout << "TEST FAILED! Wrong success!" <<std::endl;
			std::cout << "Iteration: " << i << std::endl;
			std::cout << "Golden success: " << golden_success << std::endl;
			std::cout << "DUT success: " << dut_success << std::endl;
			return 1;
		}

		if (!golden_success) continue;

		for (int j = 0; j < MAX_DEPTH; ++j) {
			if (!float_eq(10e-6, dut_out[j], golden_out[j])) {
				std::cout << "TEST FAILED! Wrong out!" <<std::endl;
				std::cout << "Iteration: " << i << std::endl;
				std::cout << "Position: " << j << std::endl;
				std::cout << "Golden out: " << golden_out[j] << std::endl;
				std::cout << "DUT out: " << dut_out[j] << std::endl;
				return 1;
			}
		}
	}
	std::cout << "TESTS PASSED!" << std::endl;
}
