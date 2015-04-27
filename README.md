# Final-Project

#### In defense of multiple inheritance
I chose to use a class (HashMap) that utilizes multiple inheritance (of Graph and HashTable) over composition based on the idea that HashMap is expected to function like both a graph and a hash table in every sense, choosing which structure to favor based on strengths. In other words, HashMap is expected to have the ability to be used in place of a graph or hash table in every application, lending to inheritance.

#### State of the program
Not willing to give up a self-nesting templated hashtable class for too long made me run out of time as of Sunday. I'm going to continue to update the program throughout at least the next week, but at the moment it feels like a really heavy and useless graph because there are no edges, and that means it has no real purpose other than being a perfect hash table for no gain.
The Makefile is grossly untested.

### Project Summary
This program takes a comma separated value (.csv or any text files that are comma delim'd) document of colorado 14ers and builds a graph around it.
However, since the weakness of a graph is it's O(n) access times, I merged a graph with a hashtable to reduce the access/modify times. But since a hash table can approach O(n) time depending on the hash function and table size, I opted for a 'perfect' hash table to make access O(1) constant.


### How To Run
Clone into `https://github.com/Aetas/Prince-CSCI2270-FinalProject` and compile.

In the terminal, run `HashMap.o` to start the program without specifying a file.

To start the program with the program specified, run `HashMap.o 14ers.csv`.

If the file is not found, it is likely not in the same directory as the executable, in which case either put them in the same directory or run `HashMap.o ../path/to/dir/14ers.csv`.


### Dependencies
GCC, Clang, or VC++ compiler up to c++11, or c++0x
- Yes, XCode uses Clang. Or rather an almost identical version from the LLVM.

This only uses the standard libraries.

If you intend to use the Makefile then Make will be required. The simple Unix like make is fine if GNU is not an option.

To get Make on Debian distributions, copy+paste into terminal:
```
sudo apt-get install build-essential
```
Chances are this is already installed, otherwise you won't have a compiler in the first place...

To get Make on a RHEL machines, copy+paste into terminal:

for the whole dev package needed for compiling...
```
sudo yum groupinstall 'Development Tools'
```
or for just make...
```
sudo yum install make
```

`sudo yum list | grep Make*` works wonders as well.

### System Requirements
A terminal environment. 32 or 64 bit, though there shouldn't be any reason 16 wouldn't work. Probably.

Windows/Deb-distributions/RHEL-distirbutions/Unix-like distributions (BSD/Mac/etc) should all be fine.

### Compiling
#### Windows
Windows has a version of unix-make that I have never used but should work fine. There are no GNU Make features in the Makefile to ruin things. Except maybe vpath if you choose to uncomment that bit.

Compile normally with visual studio as a project. Set header path to the HashMap.h location

It is possible to compile with MSBuild from command line as well... But GCC/Clang is the only option I have explored.
#### Mac
Unfortunately I no longer have a mac to test this on. If compiling from the terminal, follow a Unix-like OS instruction set.

If someone has experience with Mac compiling, feel free to update this.
#### Unix-like - GCC
Type `g++ --version` and make sure -std=c++0x or -std=c++1 [is supported](https://gcc.gnu.org/projects/cxx0x.html) by your version. Chances are very good that it is.

From the base cloned directory copy in... `g++ -Wall -Werror -std=c++0x ./src/driver.cpp ./src/HashTable.cpp ./include/HashTable.h -o HashTable.o`
#### Unix-like - Clang
TBA
Type `clang --version` into the terminal and check the version to make sure basic c++11 [is supported](http://clang.llvm.org/cxx_status.html). 

#### Unix-like - Make
Navigate into the cloned directory from terminal and type `Make`

### Group Members
Yours truly

### Contributors
[14ers](14ers.com) for generating the initial ranked .csv file. Nobody likes to type out 53 lines of CSV. Just kidding, I had to type in all of the coordinates and make the edge file.

### Open Issues/bugs
- There are probably a veritable s***-load hiding. Some of the 'bugs' (if they can be called that since it's by design) are simply coded to be circumvented purely because it's a functionality that is not supported. Nor was it really intended to be, but I might revisit it later.

### Contributing
There are a few things I try to maintain in my code...
- Name spaces are never declared in implementation or header files, 'std::<command>' is preferred
- Memory is never allocated in a header file. Which can be hard to follow with the next point
- Templated functions and classes remain in the header files with their implementations
- If a header file is going to use a large number of #includes, it is best to split the header up into multiple based on their #includes, if permitted. Circular including is not possible.
- If it is going to use a hash-look-up and a graph implementation, overload it in HashMap
- There are some naming conventions mentioned in the header file that I tried to follow loosely
  * Full names are preferred over abbreviations
  * Caps on every word is preferred in type/container declarations so that the lower case version can be a variable
  * Making at least as many spelling errors as I do is highly encouraged.
- For the most part, I'm just putting this body of text here because I needed to have something down.
