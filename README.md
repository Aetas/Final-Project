# Final-Project

#### In defense of multiple inheritance
I chose to use a class (HashMap) that utilizes multiple inheritance (of Graph and HashTable) over composition based on the idea that HashMap is expected to function like both a graph and a hash table in every sense, choosing which structure to favor based on strengths. In other words, HashMap is expected to have the ability to be used in place of a graph or hash table in every application, lending to inheritance.

#### State of the program
Runs fine. No problems that have been found. Time constraints and stubbornness surrounding class implementations and templates caused a distinct lack of edges to be found on this graph. For now. But it is still a 'perfect' hashing table at heart, so that's fine at the moment.

### Project Summary
This program takes a comma separated value (.csv or any text files that are comma delim'd) document of colorado 14ers and builds a graph around it.
However, since the weakness of a graph is it's O(n) access times, I merged a graph with a hashtable to reduce the access/modify times. But since a hash table can approach O(n) time depending on the hash function and table size, I opted for a 'perfect' hash table to make access O(1) constant.

GNUPerf would have saved me a lot of trouble a week ago.


### How To Run
Clone into `https://github.com/Aetas/Prince-CSCI2270-FinalProject` and compile. (instructions below)

In the terminal, run `HashMap.out` to start the program without specifying a file.

To start the program with the data file specified, run `HashMap.out 14ers.csv`.

If the file is not found, it is likely not in the same directory as the executable, in which case either put them in the same directory or run `HashMap.out ../path/to/dir/14ers.csv`.


### Dependencies
GCC, Clang, or VC++ compiler up to c++11, or c++0x code standards
- XCode uses Clang

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
... will likely get you where you need to be if all else fails.

`sudo yum list | grep Make*` works wonders as well.

### System Requirements
A terminal environment. 32 or 64 bit, though there shouldn't be any reason 16 wouldn't work. Probably.

Windows/Deb-distributions/RHEL-distirbutions/Unix-like distributions (BSD/Mac/etc) should all be fine.

### Compiling
#### Standard Terminal Environment - Unix-like
* Make sure g++ is up to at least c++0x standards by typing `gcc --version` and checking it [against this list](https://gcc.gnu.org/projects/cxx0x.html).
* Follow these commands to clone and build the program (note - clone your fork instead if you intend to push commits):
```
git clone https://github.com/Aetas/Prince-CSCI2270-FinalProject
cd ./Prince-CSCI2270-FinalProject
sh build.sh
cd ./bin
make
```
Run the program by typing `./HashMap.out` or `./HashMap.out 14ers.csv`

* If any of the steps say there is no executable to run then run `sudo chmod u+x ./file_name` on it.

#### Windows
1. Windows has a version of unix-make that I have never used but should work fine. Just make sure all the files are in the same directory, as windows doesn't fare well with bash scripts. Then run `make` as per usual.

2. Compile with visual studio as a project. Set header path to the `HashMap.h` location or write `#include"../include/HashMap.h`

3. It is possible to compile with MSBuild from command line as well... But it is not an option I have explored.

#### Clang
* Clang will work fine if it is up to [c++11 standards](http://clang.llvm.org/cxx_status.html).
Unfortunately I do not have much experience with clang to give detailed instructions.

There are some commented out lines in the make file surrounding clang, but I never game them an honest effort.

### Group Members
Yours truly

### Contributors
[14ers](14ers.com) for generating the initial ranked .csv file. Nobody likes to type out 53 lines of CSV. Just kidding, I had to type in all of the coordinates and make an edge file.

### Open Issues/bugs
- TBA

### Contributing
Just a few things that might make the structure of my code more understandable. Read if you will. Or don't. That's just as good, honestly.
- Name spaces are never declared in implementation or header files, 'std::<command>' is preferred
- Memory is never allocated in a header file. Which can be hard to follow with the next point
- Templated functions and classes remain in the header files with their implementations
- If a header file is going to use a large number of #includes, it is best to split the header up into multiple based on their #includes, if permitted. Circular including is not possible.
- If it is going to use a hash-look-up and a graph implementation, overload it in HashMap
- There are some naming conventions mentioned in the header file that I tried to follow loosely
  * Full names are preferred over abbreviations
  * Caps on every word is preferred in type/container declarations so that the lower case version can be a variable
  * Making at least as many spelling errors as I do is highly encouraged.
- Declaring containers/variables after all conditions are met. E.g. a queue does not need to be made before it is determined that there is anything to fill it. RAII is also nice practice I suppose.
- For the most part, I'm just putting this body of text here because I needed to have something down.
