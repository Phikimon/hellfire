CFLAGS := -c -std=c99
all: fire tags

fire: main.o terminal.o flame.o spread_fire.o
	gcc -o $@ $^ -lm

%.o: %.c terminal.h flame.h spread_fire.h
	gcc $(CFLAGS) $< -o $@

tags:
	ctags -R . || /dev/true

clean:
	rm fire *.o tags 2> /dev/null
