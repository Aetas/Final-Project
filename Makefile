#sheblamo

#Same as saying CXX
CC = g++
CPPFLAGS = -Wall -Werror -std=c++0x
OBJ = main.o functions.o
OUTPUT = HashMap.o
ODIR = ./bin
PROJ_DIR = $(HOME)/home/aetas/gitrepos/final

vpath = %.h  $(PROJ_DIR)/include
vpath = %.cpp $(PROJ_DIR)/src

program: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(ODIR)

main.o : ./src/driver.cpp ./include/HashMap.h
	$(CC) $(CPPFLAGS) -c

functions.o : ./src/HashMap.cpp ./include/HashMap.h
	$(CC) $(CPPFLAGS) -c

.PHONY : clean
clean :
	rm program $(OBJ)

# Creates a log to keep track of things changed
# log : driver.cpp $(OBJ)
# 	lpt -p $?
# 	touch log
