CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
INCLUDES = -Iinclude
SRC = main.c Kasiski.c Frequencias.c Vigenere.c
OBJ = $(SRC:.c=.o)
EXEC = vigenere_decrypt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
