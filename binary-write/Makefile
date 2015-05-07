#sheblamo

#this makefile is so small it's almost insulting
CXX = g++
CXXFLAGS = -std=c++0x -Wall -Werror
#I had expected to use a header file for this. Now it's just silly.
OBJ = main.o

all : program

program : $(OBJ)
	$(CXX) $(CXXFLAGS) -o binary-write $(OBJ)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean :
	rm *.o

uninstall :
	rm binary-write
