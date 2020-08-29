CC = g++
CPPFLAGS = -std=c++17 -Wall -Werror -pedantic 
LIB = libclasses.a
LIBOBJS = Backlog.o Board.o Message.o SocialNetwork.o Task.o User.o Worker.o
BUILD = $(LIB)

.PHONY: all clean util

all: $(BUILD)

$(LIB): $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

Backlog.o: Backlog.h

Board.o: Board.h

Message.o: Message.h

SocialNetwork.o: SocialNetwork.h

Task.o: Task.h

User.o: User.h

Worker.o: Worker.h

clean:
	rm -f $(wildcard *.o)
	rm -f $(BUILD)
	rm -f core
	rm -f a.out
