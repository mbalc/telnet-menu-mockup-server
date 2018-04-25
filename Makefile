TARGET: echo-server

CC		= g++
CXXFLAGS	= -Wall -Wextra -std=c++17

all: CXXFLAGS	+= -O2
all: CCFLAGS	+= -O2
all: echo-server

debug: CXXFLAGS	+= -O0 -DDEBUG -g
debug: CCFLAGS	+= -O0 -DDEBUG -g
debug: echo-server

echo-server.o err.o: err.h

echo-server: echo-server.o err.o
	$(CC) $(CXXFLAGS) $^ -o $@

.PHONY: clean TARGET debug

clean:
	rm -f echo-server *.o *~ *.bak
