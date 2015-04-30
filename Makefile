#sheblamo

#Same as saying nothing
CXX = g++
CLANG = clang++
CXXFLAGS = -Wall -Werror -std=c++0x
LLVMFLAGS = -Weverything -std=c++11 -stdlib=libc++
OBJ = HashMap.o driver.o
OUTPUT = HashMap.out

vpath %.h ./include
vpath %.cpp ./include

all : gcc

gcc : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJ)

driver.o : driver.cpp HashMap.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

HashMap.o : HashMap.cpp HashMap.h
	$(CXX) $(CXXFLAGS) -c HashMap.cpp

#Nope.
clang : $(OBJ)
	$(CLANG) $(LLVMFLAGS) $(OBJ) -o $(OUTPUT)

# Ignore these. Just playing around with clang's error messages. Nothing to see here.
header.o : HashMap.h
	$(CLANG) $(LLVMFLAGS) -c

fn.o : HashMap.h HashMap.cpp
	$(CLANG) $(LLVMFLAGS) -c

drive.o : driver.cpp HashMap.h HashMap.cpp
	$(CLANG) $(LLVMFLAGS) -c


.PHONY : clean
clean :
	rm *.o

# Creates a log to keep track of things changed
 #log : driver.cpp $(OBJ)
 #	lpt -p $?
 #	touch log
