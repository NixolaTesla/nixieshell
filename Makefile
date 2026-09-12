CC = gcc
CFLAGS = -Wall -Wextra -std=c11

program: nixieshell.c
	$(CC) $(CFLAGS) nixieshell.c -o Nixie


clean:
	rm -rf Nixie
