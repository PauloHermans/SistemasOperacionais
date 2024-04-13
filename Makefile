DEBUG_CARGS =

ifdef $(DEBUG)
DEBUG_CARGS = -g
endif

CC    = cc
CARGS = -std=c2x -Wall -Wextra $(DEBUG_CARGS)
LIBS  = -lpthread -lrt

.PHONY: clean default

default:
	@echo 'Please type a target to run.'

clean:
	rm -vf conveyor_pipe_problematic conveyor_thread conveyor_pipe_threaded

conveyor_pipe_problematic: conveyor_pipe_problematic.c conveyor_shared.c
	$(CC) $(CARGS) -o $@ $^ $(LIBS)

conveyor_pipe_threaded: conveyor_pipe_threaded.c conveyor_shared.c
	$(CC) $(CARGS) -o $@ $^ $(LIBS)

conveyor_thread: conveyor_thread.c conveyor_shared.c
	$(CC) $(CARGS) -o $@ $^ $(LIBS)
