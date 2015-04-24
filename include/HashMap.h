#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#define PRIMARY_SIZE 4
#define SECONDARY_SIZE 17
#define MAX_DISTANCE 9999999

#include<string>
#include<vector>

/*
WIP naming conventions
	If it is an attribute of an object, and underscore is used to denote object-attribute relation <object>_<attribute> is used. 
	If it is a method or unique attribute, no underscore is used and caps denote words.
	Whole words are prefered over abbreviations
	Caps are used in object declarations so a mountain can be declared as Mountain* mountain = new Mountain();
*/


//Since inheritance is used, making the compiler happy is needed
//The classes/structs are listed in the order they appear as a way to keep track of them
class Edge;
class Mountain;
template<class T> class HashTable_Perfect;
class Graph;
//class HashMap;

//---------EDGE---------//
//This became a class out of chance. Largely because I had the construct/destruct inlined, 
//but it needed a complete mountain type to call delete on. So now not so much
class Edge {
	//construct/destruct
	Edge();
	Edge(Mountain* destination, int& in_weight);
	~Edge();

	Mountain* next;
	double weight;
};

//---------MOUNTAIN---------//
//vertex in the graph sense, node in the hash table sense
class Mountain {
public:
	//construct/destruct
	Mountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& NS, double& in_long, char& EW);
	Mountain(std::string&);	//make with name
	~Mountain();

	bool have_visited;		//record keeping
	double distance;		//record keeping for algs

protected:
private:
	//used for tracing paths in route finding algorithms
	Mountain* previous;

	struct Coordinates {
		char N_S, E_W;
		double latitude, longitude;
	} coordinates;

	std::string name;
	std::string range;
	int rank;
	double elevation;
	std::vector<Edge*> edge;
};

//---------GRAPH---------//
//writing traversal algorithms is going to be a f**king nightmare.
//but that's fine.
class Graph {
public:
	//construct/destruct
	Graph();
	~Graph();

	//by name
	void addEdge(int&, int&, int);	//v1, v2, weight
	void displayEdges(Mountain*);
	void BFTraversal();
	void BFTraversal(std::string&);
	Mountain* shortestPath(std::string&, std::string&);		//

protected:
	void reset_visited();	//protected because why not

private:
	//graph is sudo virtual/interface, I'm simply leaving private things so that I can write the functions for graph
	//and have them implement in HashMap
	std::vector<Edge*> Prim_edge;
	std::vector<Mountain*> range;
};

//---------HASHTABLE_PERFECT---------//
//My perfect hashtable w/ templates
template<class T> class HashTable_Perfect {
public:
	HashTable_Perfect() {
		size = 0;
		hashTable = new T*[SECONDARY_SIZE];
		for (unsigned int i = 0; i < SECONDARY_SIZE; i++)
			hashTable[i] = nullptr;
	}
	HashTable_Perfect(int s_size) {				//specify size of second table
		size = 0;
		hashtable = new T*[s_size];
	}
	~HashTable_Perfect() {
		if (size > 0)
			delete[]hashTable;
	}

	void printInventory() {
		if (size == 0) {
			std::cout << "empty" << std::endl;	//I'm only tolerating a print in this function because it is a print function.
			return;
		}
		for (int i = 0; i < H_TABLE_SIZE; i++) {
			if (hashTable[i] == nullptr)
				continue;	//skip rest
			std::cout << hashTable[i]->title << ":" << hashTable[i]->year << std::endl;
		}
	}
	unsigned int get_size() {
		return size;
	}
	bool is_empty() {
		return (size == 0);
	}
	template<typename K>
	T* operator[](K key) {
		return this->hashTable[key];
	}

	T** hashTable;

	//I'll come back top this later when it can determine it's own size
	unsigned int*& populateKeys(std::string& in_name) {
		unsigned int* keys = new unsigned int[2];
		int sum = 0;
		for (unsigned int i = 0; i < in_name.size(); i++)
			sum += in_name[i];
		keys[0] = sum % PRIMARY_SIZE;
		keys[1] = keys[0] % SECONDARY_SIZE;
		return keys;
	}
protected:
	unsigned int size;
private:
};

//---------HASHMAP---------//
//to template... or not to template...
//I'm removing the template bit for now because the descision is hindering progress. I can always come back and convert/paste in templates if I need to.
//template<class T>
class HashMap : public HashTable_Perfect<Mountain>, public Graph {
public:
	HashMap() {};
	~HashMap() {};

	void insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew);
	void deleteMountain(std::string& in_name);
	
	Mountain* findMountain(std::string& in_name);

	unsigned int size_of();
	bool is_empty();

protected:
private:
	HashTable_Perfect<Mountain>** hashTable;
	std::vector<Edge*> edge;
	std::vector<Mountain*> range;	//vertices
};

#endif //MOUNTAIN_H