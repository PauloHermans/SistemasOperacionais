#include <stdio.h>
#include <windows.h>
#include "conveyor_shared.h"

#define PIPE1_NAME "\\\\.\\pipe\\esteirapipe1"
#define PIPE2_NAME "\\\\.\\pipe\\esteirapipe2"

int main() {

	HANDLE pipe1, pipe2;
	DWORD bytesRead;
	CHAR buffer[1024];

	setvbuf(stdout, NULL, _IONBF, 0);

	pipe1 = CreateNamedPipe(PIPE1_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	pipe2 = CreateNamedPipe(PIPE2_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024, 1024, NMPWAIT_USE_DEFAULT_WAIT, NULL);

	if (pipe1 == INVALID_HANDLE_VALUE) {
		printf("Erro em criar o pipe1.\n");
		return 1;
	}

	if (pipe2 == INVALID_HANDLE_VALUE) {
		printf("Erro em criar o pipe2.\n");
		return 1;
	}

	if (ConnectNamedPipe(pipe1, NULL) == FALSE) fprintf(stderr, "pane1"), exit(-1);
	if (ConnectNamedPipe(pipe2, NULL) == FALSE) fprintf(stderr, "pane2"), exit(-1);

	while (1) {

		/* Ler pipe1 */
		ReadFile(pipe1, buffer, sizeof(buffer), &bytesRead, NULL);
		data_apply_values((double) atoi(buffer));

		/* Ler pipe2 */
		ReadFile(pipe2, buffer, sizeof(buffer), &bytesRead, NULL);
		data_apply_values((double) atoi(buffer));

		display_update_count();
		display_print_display();

		Sleep(2000); // Atualiza a cada 2 segundos
	}

	return 0;
}
