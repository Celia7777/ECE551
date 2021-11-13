CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 
OBJS=$(patsubst %,%.o,$(PROGS)) page.o 
all: $(PROGS)
cyoa-step%: cyoa-step%.o page.o 
	g++ -o $@ $^
%.o: %.c
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

page.o: page.cpp

