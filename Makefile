#sheblamo

#Same as saying nothing
CXX = g++
CLANG = clang
CXXFLAGS = -Wall -Werror -std=c++0x
LLVMFLAGS = -Werror -Weverything -std=c++11
OBJGCC = header_gcc.o functions_gcc.o driver_gcc.o
OBJLLVM = header_clang.o functions_clang.o driver_clang.o
OUTPUT = HashMap.o

vpath %.h ./include
vpath %.cpp ./include

gcc : allgcc

allgcc : ./include/HashMap.h ./src/HashMap.cpp ./src/driver.cpp
	$(CC) $(CXXFLAGS) ./include/HashMap.h ./src/HashMap.cpp ./src/driver.cpp -o $(OUTPUT)


#gcc : $(OBJGCC)
#	$(CC) $(CXXFLAGS) $(OBJGCC) -o $(OUTPUT) $(OBJGCC)

clang : $(OBJCLANG)
	$(CLANG) $(LLVMFLAGS) $(OBJCLANG) -o $(OUTPUT)

driver_gcc.o : driver.cpp header_gcc.o functions_gcc.o
	$(CC) $(CXXFLAGS) -c

functions_gcc.o : HashMap.cpp header_gcc.o
	$(CC) $(CXXFLAGS) -c

header_gcc.o : HashMap.h
	$(CC) $(CXXFLAGS) -c 

driver_clang.o : driver.cpp header_gcc.o functions_gcc.o
	$(CC) $(CXXFLAGS) -c

functions_clang.o : HashMap.cpp header_gcc.o
	$(CC) $(CXXFLAGS) -c

header_clang.o : HashMap.h
	$(CC) $(CXXFLAGS) -c 

.PHONY : clean
clean :
	rm *.o

# Creates a log to keep track of things changed
 #log : driver.cpp $(OBJ)
 #	lpt -p $?
 #	touch log
