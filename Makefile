DEBUG_CARGS  =
TIMING_CARGS =

ifeq ($(DEBUG),1)
DEBUG_CARGS = -g
endif

ifeq ($(TIMING),1)
TIMING_CARGS = -DTIMING
endif

CC    = cc
CARGS = -std=c11 -Wall -Wextra $(DEBUG_CARGS) $(TIMING_CARGS)
LLIBS = -lpthread -lrt
WLIBS = -lpthread -lucrt

WINCC = x86_64-w64-mingw32-gcc

.PHONY: clean default

default:
	@echo 'Please type a target to run.'

clean:
	rm -vf conveyor_pipe_problematic conveyor_thread conveyor_pipe_threaded

conveyor_pipe_problematic: conveyor_pipe_problematic.c conveyor_shared.c conveyor_shared.h
	$(CC) $(CARGS) -o $@ $^ $(LLIBS)

conveyor_pipe_threaded: conveyor_pipe_threaded.c conveyor_shared.c conveyor_shared.h
	$(CC) $(CARGS) -o $@ $^ $(LLIBS)

conveyor_thread: conveyor_thread.c conveyor_shared.c conveyor_shared.h
	$(CC) $(CARGS) -o $@ $^ $(LLIBS)

windows_thread: conveyor_thread.c conveyor_shared.c conveyor_shared.h
	$(WINCC) $(CARGS) -DWINDOWS -D_UCRT -o $@ $^ $(WLIBS) -static

windows_pipe_threaded: conveyor_pipe_threaded.c conveyor_shared.c conveyor_shared.h
	$(WINCC) $(CARGS) -DWINDOWS -D_UCRT -o $@ $^ $(WLIBS) -static
