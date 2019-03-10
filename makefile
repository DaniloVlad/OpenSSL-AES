# the compiler: gcc for C program, define as g++ for C++
  CC = gcc

# compiler flags:
CFLAGS  = -g -Wall

main: main.c aes.c
	$(CC) main.c $(CFLAGS) -lcrypto aes.c -o main

clean:
	$(RM) main