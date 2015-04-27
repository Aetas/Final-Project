#sheblamo

#Same as saying CXX
CC = g++
CLANG = clang
CPPFLAGS = -Wall -Werror -std=c++0x
LLVMFLAGS = -tbd
OBJ = main.o functions.o header.o
OUTPUT = HashMap.o

program: 
	$(CC) $(CPPFLAGS) driver.cpp HashMap.cpp HashMap.h -o $(OUTPUT)

gcc : $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(OUTPUT)

clang : $(OBJ)
	$(CLANG) $(LLVMFLAGS) -stuff $(OUTPUT)

.PHONY : clean
clean :
	rm program gcc clang

 Creates a log to keep track of things changed
 log : driver.cpp $(OBJ)
 	lpt -p $?
 	touch log
