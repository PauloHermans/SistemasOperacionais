#ifndef CONVEYOR_SHARED_H_
#define CONVEYOR_SHARED_H_

#define CONVEYOR1_WAIT_TIME 2000000
#define CONVEYOR2_WAIT_TIME 1000000

#define CONVEYOR1_ITEM_WEIGHT 5.0f
#define CONVEYOR2_ITEM_WEIGHT 2.0f

#define CONTROLLER_WAIT_TIME 2000000

#define DISPLAY_UPDATE_WEIGHT_ON_NTH 500 

struct conveyor_data
{
	int    items_read;
	double accumulated_weight;
};

extern struct conveyor_data data;
extern struct conveyor_data display;

void display_print_display(void);

void display_update_weight(void);
void display_update_count (void);
void data_apply_values    (double weight);

#ifdef    TIMING

#include <time.h>

extern struct timespec conveyor1_timing_old, conveyor1_timing_new;
extern struct timespec conveyor2_timing_old, conveyor2_timing_new;

void timing_register(struct timespec* t);
void timing_log     (const char which, struct timespec* a, struct timespec* b);

#endif // TIMING

#endif // CONVEYOR_SHARED_H_
