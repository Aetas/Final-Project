#sheblamo

#Same as saying CXX
CC = g++
CLANG = clang
CPPFLAGS = -Wall -Werror -std=c++0x
LLVMFLAGS = -Werror -Weverything -std=c++11
OBJGCC = header_gcc.o functions_gcc.o driver_gcc.o
OBJLLVM = header_clang.o functions_clang.o driver_clang.o
OUTPUT = HashMap.o

vpath %.h ./include
vpath %.cpp ./include

gcc :./include/HashMap.h ./src/HashMap.cpp ./src/driver.cpp
	$(CC) $(CPPFLAGS) ./include/HashMap.h ./src/HashMap.cpp ./src/driver.cpp -o $(OUTPUT)


#gcc : $(OBJ)
#	$(CC) $(CPPFLAGS) $(OBJGCC) -o $(OUTPUT)

clang : $(OBJ)
	$(CLANG) $(LLVMFLAGS) $(OBJCLANG) -o $(OUTPUT)

driver_gcc.o : driver.cpp header_gcc.o functions_gcc.o
	$(CC) $(CPPFLAGS) -c

functions_gcc.o : HashMap.cpp header_gcc.o
	$(CC) $(CPPFLAGS) -c

header_gcc.o : HashMap.h
	$(CC) $(CPPFLAGS) -c 

driver_clang.o : driver.cpp header_gcc.o functions_gcc.o
	$(CC) $(CPPFLAGS) -c

functions_clang.o : HashMap.cpp header_gcc.o
	$(CC) $(CPPFLAGS) -c

header_clang.o : HashMap.h
	$(CC) $(CPPFLAGS) -c 

.PHONY : clean
clean :
	rm *.o

# Creates a log to keep track of things changed
 #log : driver.cpp $(OBJ)
 #	lpt -p $?
 #	touch log
