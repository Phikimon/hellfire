INCLUDE_DIR := ./include
SRC_DIR := ./src

CFLAGS := -c -std=c99 -I $(INCLUDE_DIR) -I.
LIBS := -lm
LFLAGS :=

DEPS := $(INCLUDE_DIR)/terminal.h $(INCLUDE_DIR)/flame.h $(INCLUDE_DIR)/spread_fire.h
OBJS := $(SRC_DIR)/main.o $(SRC_DIR)/terminal.o $(SRC_DIR)/flame.o $(SRC_DIR)/spread_fire.o

all: fire tags

fire: $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^ $(LIBS)

%.o: $(SRC_DIR)/%.c $(DEPS)
	gcc $(CFLAGS) $< -o $@

tags:
	ctags -R . || /dev/true

clean:
	rm fire $(SRC_DIR)/*.o tags 2> /dev/null
