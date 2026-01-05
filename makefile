# Team 8 - SysForge
# Members: Colten Mikulastik, Mayuresh Keshav Kamble, Nathanlie Ortega, Igor Leeck
# Course: CSCE 3600.002
# Date: December 4, 2025
# Description: Makefile for Major Assignment 2

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic

TARGET = newshell

# TODO: Object files - Guys, Please add your .o files as you complete them for both Built In Commands and Advanced Features!!

OBJS = main.o path.o cd.o alias.o exit.o pipeline.o myhistory.o redirection.o signalhandler.o


$(TARGET): $(OBJS)

	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "========================================"
	@echo "Compilation successful!"
	@echo "Run the shell with: ./$(TARGET)"
	@echo "========================================"

# nathanlie's object file compilation
main.o: main.c shell.h
	$(CC) $(CFLAGS) -c main.c

cd.o: cd.c shell.h
	$(CC) $(CFLAGS) -c cd.c

alias.o: alias.c shell.h
	$(CC) $(CFLAGS) -c alias.c

# colten's object file compilations
path.o: path.c shell.h

	$(CC) $(CFLAGS) -c path.c

redirection.o: redirection.c shell.h
	$(CC) $(CFLAGS) -c redirection.c
# Colten TODO: add second part later

# Mayuresh's object file compilations
exit.o: exit.c exit.h shell.h
	$(CC) $(CFLAGS) -c exit.c

pipeline.o: pipeline.c pipeline.h shell.h
	$(CC) $(CFLAGS) -c pipeline.c

# Igor's object file compilations
myhistory.o: myhistory.c shell.h myhistory.h
	$(CC) $(CFLAGS) -c myhistory.c

signalhandler.o: signalhandler.c shell.h signalhandler.h
	$(CC) $(CFLAGS) -c signalhandler.c


clean:
	rm -f *.o $(TARGET)
	@echo "Clean complete"
