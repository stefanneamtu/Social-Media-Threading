CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -pedantic -Ilib -g
LDLIBS = -Llib -lclasses -lpthread
BUILD = libs main

.PHONY: all clean libs

all: $(BUILD)

main: main.o

clean:
	rm -f $(wildcard *.o)
	rm -f $(BUILD)
	rm -f core
	rm -f a.out
	rm -rf *.bin
	cd lib; make clean

libs:
	cd lib; make

