#include "conveyor_shared.h"
#include <stdio.h>

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
