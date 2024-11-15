obj = object/
CC = g++
flag = -c
warn_flag = -Wall -Wextra
all: proc

proc: stack.o proces.o
	$(CC) $(warn_flag) $(obj)stack.o $(obj)proces.o -o proc.exe  
stack.o: stack.cpp
	$(CC) $(warn_flag) $(flag) $^ -o $(obj)$@
proces.o: proc.cpp
	$(CC) $(warn_flag) $(flag) $^ -o $(obj)$@
