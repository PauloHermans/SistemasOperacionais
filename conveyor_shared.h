#ifndef CONVEYOR_SHARED_H_
#define CONVEYOR_SHARED_H_

/* Constântes */
#define CONVEYOR1_WAIT_TIME 2000000
#define CONVEYOR2_WAIT_TIME 1000000

#define CONVEYOR1_ITEM_WEIGHT 5.0f
#define CONVEYOR2_ITEM_WEIGHT 2.0f

#define CONTROLLER_WAIT_TIME 2000000

#define DISPLAY_UPDATE_WEIGHT_ON_NTH 500 

/* Esta estrutura guarda os dados coletados das esteiras */
struct conveyor_data
{
	int    items_read;
	double accumulated_weight;
};

/* 
 * 'data' guarda os valores coletados reais, enquanto 'display' guarda
 * oquê está sendo mostrado na tela.
 */
extern struct conveyor_data data;
extern struct conveyor_data display;

/* Mostra 'display' no terminal */
void display_print_display(void);

/* 
 * Copia de 'data' -> 'display' os valores de 
 * pesagem e contagem respectivamente 
 */
void display_update_weight(void);
void display_update_count (void);

/*
 * Acumula o valor 'weight' e incrementa a contagem de items.
 */
void data_apply_values    (double weight);

/* 
 * Este é o codigo de benchmark.
 * É necessário compilar com make ... TIMING=1
 */
#ifdef    TIMING

#include <time.h>

/*
 * Os pares de valores old:new no formato timespec (segundo, nanosegundo).
 */
extern struct timespec conveyor1_timing_old, conveyor1_timing_new;
extern struct timespec conveyor2_timing_old, conveyor2_timing_new;

/*
 * Registra o tempo em um timespec.
 *
 * A primeira call deve ser dirigida a um xyz_old.
 * A segunda  call a um xyz_new.
 */
void timing_register(struct timespec* t);

/* 
 * Subtraí dois timespecs e loga no stderr. 'which' é o nome da thread (um charactére somente).
 */
void timing_log     (const char which, struct timespec* a, struct timespec* b);

#endif // TIMING

#endif // CONVEYOR_SHARED_H_
