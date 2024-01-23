#ifndef _FILTER

#include <stdbool.h>

#define _FILTER

#define MAX_DEPTH 10
void getFilterOut (
		int inputs[MAX_DEPTH],
		unsigned short depth,
		int out[MAX_DEPTH],
		bool* out_correct
		);

#endif
