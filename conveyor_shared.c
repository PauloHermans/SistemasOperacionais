#define _DEFAULT_SOURCE
#include <stdio.h>
#include <time.h>
#include "conveyor_shared.h"
#ifdef WINDOWS
#include <windows.h>
#endif

/* 
 * Definição dos armazenametnos (é uma variavel global 
 * compartilhada entre varios arquivos C. 
 */
struct conveyor_data data    = {0};
struct conveyor_data display = {0};

/* Updates */
void display_update_weight(void) { display.accumulated_weight = data.accumulated_weight; }
void display_update_count (void) { display.items_read         = data.items_read;         }

/* 
 * Mostra o display na tela
 * É usado o '\r' invés do '\n' para que o display fique sempre
 * na mesma linha. Note que é necessário configurar o stdout para
 * que não trave a saída até o proximo line feed, já que este nunca
 * será emitido. Veja conveyor_thread.c.
 */
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

/* 
 * Acumula o peso especificado e incrementa a contagem de items.
 * No DISPLAY_UPDATE_WEIGHT_ON_NTH-ésimo item o display de peso
 * acumulado é automaticamente atualizado.
 */
void data_apply_values(double weight)
{

	data.accumulated_weight += weight;
	data.items_read++;

	if (data.items_read % DISPLAY_UPDATE_WEIGHT_ON_NTH == 0)
		display_update_weight();

	return;
}

/* Implementação dos benchmarks */
#ifdef    TIMING
/* Armazenamento dos timespecs. */
struct timespec conveyor1_timing_old, conveyor1_timing_new;
struct timespec conveyor2_timing_old, conveyor2_timing_new;

/* Popula um timespec com o tempo atual */
void timing_register(struct timespec* t)
{
	/*
	 * No Linux, usamos o clock_gettime monotônico do POSIX,
	 * que na minha maquina tem uma precisão mágica de 1ns
	 * (não me pergunte que tipo de magia negra foi usada
	 * para mensurar uma frequência tão alta, testes pessoais
	 * meus sugerem que este valor não é mentira.)
	 *
	 * No Windows tudo é mais complicado, e tenho certeza que
	 * o timer nanosegundo deles faz parte de alguma API obscura
	 * e obtusa, então usei o timespec_get(), que segundo as más
	 * linguas tem uma precisão (no Windows) de ~100ns.
	 */
	#ifdef WINDOWS
	timespec_get(t, TIME_UTC); 
	#else
	clock_gettime(CLOCK_MONOTONIC_RAW, t);
	#endif
	return;
}

/* 
 * Calcula a diferença entre dois timespecs e loga-o no stderr. 
 *
 * TEORIA STDIO:
 *
 *   Existem dois caminhos para um "printf" da vida escrever seu texto:
 *   stdout e stderr. O stdout é o caminho padrão, enquando o stderr é
 *   dedicado à mensagens de erro. Normalmente, ambos são mostrados no
 *   mesmo terminal, porém como são duas streams diferentes, é possivel
 *   redirecionar um e não o outro.
 *
 *   Como exemplificado no README.md, este mecanismo é usado para separar
 *   o display dos dados de benchmark via a funcionalidade de redirecionamento
 *   do Bash e CMD. Por exemplo, um jeito de separa-los é
 *
 *     $ ./conveyor_thread 2> log.txt
 *     Contagem: ...
 *     $ cat log.txt
 *     1: 0.000312...
 *     2: 0.000167...
 */
void timing_log(const char which, struct timespec* a, struct timespec* b)
{
	time_t secs = b->tv_sec  - a->tv_sec;
	long   nano = b->tv_nsec - a->tv_nsec;

	/* timespec é definido diferente no Windows? */
	#ifdef WINDOWS
	fprintf(stderr, "%c: %lli.%09li\n", which, secs, nano);
	#else
	fprintf(stderr, "%c: %li.%09li\n",  which, secs, nano);
	#endif

	return;
}
#endif // TIMING
