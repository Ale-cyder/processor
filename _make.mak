dir = ../stack/stack__/stack/
obj = object/
CC = g++
flag = -c
all: proc

proc: stack.o proces.o
	$(CC) $(obj)stack.o $(obj)proces.o -o proc.exe  
stack.o: $(dir)stack.cpp
	$(CC) $(flag) $^ -o $(obj)$@
proces.o: proc.cpp
	$(CC) $(flag) $^ -o $(obj)$@
