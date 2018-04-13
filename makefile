OPTIMIZATION=-O2

WARNING_FLAGS=-Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wfatal-errors -Werror

CFLAGS=-c -g $(DEBUG) $(OPTIMIZATION) $(WARNING_FLAGS) -ansi -pedantic -std=c++11 -fno-rtti
CC=g++

all: objdir obj/log.o

objdir:
	mkdir obj;

obj/log.o: src/log.h src/log.cpp
	$(CC) $(CFLAGS) src/log.cpp -o obj/log.o

clean:
	rm obj/*; rmdir obj;
