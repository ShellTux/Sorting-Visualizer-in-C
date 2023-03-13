CC=gcc
CFLAGS=-Wall -Wextra -g -Og -lSDL2
CFILES=main.c
DEPS=
OBJECTS=main.o
SRC=.
SOURCE=$(wildcard $(SRC)/*.c)

all: main.o run

%:%.o
	$(CC) $(CFLAGS) -o $@ $^ $(DEPS) 

%.o:%.c
	@printf "\n"
	@printf "##################\n"
	@printf "Building %s\n" $@
	@printf "##################\n"
	@printf "\n"
	$(CC) $(CFLAGS) -o $@ $^ $(DEPS)

%.s: %.c
	$(CC) -S $^

run: main.o
	@printf "\n"
	@printf "###############\n"
	@printf "#   Running   #\n"
	@printf "###############\n"
	@printf "\n"
	./main.o

help:
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECTS)"

# cleaning everything that can be automatically recreated with "make".
clean:
	@printf "Cleaning\n"
	rm $(OBJECTS)
