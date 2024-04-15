#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include "conveyor_shared.h"

#define PIPE_NAME "\\\\.\\pipe\\esteirapipe2"

int main() {

	HANDLE pipe;
	DWORD  nbytes;
	CHAR   message[1024];

	pipe = CreateFile(PIPE_NAME, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (pipe == INVALID_HANDLE_VALUE) fprintf(stderr, "failed to open pipe\n"), exit(1);

	while (true) {

		#ifdef TIMING
		timing_register(&conveyor2_timing_old);
		#endif

		sprintf(message, "%d", 2);
		WriteFile(pipe, message, sizeof(message), &nbytes, NULL);

		#ifdef TIMING
		timing_register(&conveyor2_timing_new);
		timing_log('2', &conveyor2_timing_old, &conveyor2_timing_new);
		#endif

		Sleep(1000); // Atualiza a cada 1 segundo
	}

	return 0;
}
