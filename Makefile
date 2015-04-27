#sheblamo

#Same as saying CXX
CC = g++
CPPFLAGS = -Wall -Werror -std=c++0x
OBJ = main.o functions.o header.o
OUTPUT = HashMap.o

program: 
	$(CC) $(CPPFLAGS) driver.cpp HashMap.cpp HashMap.h -o $(OUTPUT)

#main.o : driver.cpp functions.o
#	$(CC) $(CPPFLAGS) -c driver.cpp

#functions.o : HashMap.cpp header.o
#	$(CC) $(CPPFLAGS) -c HashMap.cpp

#header.o : HashMap.h
#	$(CC) $(CPPFLAGS) -c HashMap.h

.PHONY : clean
clean :
	rm program

# Creates a log to keep track of things changed
# log : driver.cpp $(OBJ)
# 	lpt -p $?
# 	touch log
