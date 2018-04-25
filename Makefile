TARGET: echo-server

CC	= g++
LFLAGS	= -Wall -Wextra -O2 -std=c++17

echo-server.o err.o: err.h

echo-server: echo-server.o err.o
	$(CC) $(LFLAGS) $^ -o $@

.PHONY: clean TARGET
clean:
	rm -f echo-server *.o *~ *.bak
