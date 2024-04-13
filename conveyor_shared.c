#define _DEFAULT_SOURCE
#include <stdio.h>
#include <time.h>
#include "conveyor_shared.h"

struct conveyor_data data    = {0};
struct conveyor_data display = {0};

void display_update_weight(void) { display.accumulated_weight = data.accumulated_weight; }
void display_update_count (void) { display.items_read         = data.items_read;         }

void display_print_display(void)
{

	printf
	(
		"\rContagem: %8i. Peso Acumulado: %8.2f.",
		display.items_read,
		display.accumulated_weight
	);	

	return;
}

void data_apply_values(double weight)
{

	data.accumulated_weight += weight;
	data.items_read++;

	if (data.items_read % DISPLAY_UPDATE_WEIGHT_ON_NTH == 0)
		display_update_weight();

	return;
}

#ifdef    TIMING
struct timespec conveyor1_timing_old, conveyor1_timing_new;
struct timespec conveyor2_timing_old, conveyor2_timing_new;

void timing_register(struct timespec* t)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, t);
	return;
}

void timing_log(const char which, struct timespec* a, struct timespec* b)
{
	time_t secs = b->tv_sec  - a->tv_sec;
	long   nano = b->tv_nsec - a->tv_nsec;

	fprintf(stderr, "%c: %li.%09li\n", which, secs, nano);

	return;
}
#endif // TIMING
