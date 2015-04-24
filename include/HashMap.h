#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#define PRIMARY_SIZE 10
#define SECONDARY_SIZE 10
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
template<class T> class HashTable;

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

//---------HASHTABLE_PERFECT---------//
//SIDE PROJECT -- TRYING TO SEE IF I CAN TEMPLATE A HASHTABLE CLASS
//CAPSLOCK IS CRUISE CONTROLL FOR COOL.
template<class T> class HashTable_Perfect {
public:
	HashTable_Perfect();
	HashTable_Perfect(int& in_size);
	~HashTable_Perfect();

	void printInventory();
	unsigned int get_size();
	bool is_empty();

	//template<typename K>
	T* operator[](int key) {
		return hashTable[key];
	}
	T** hashTable;
protected:
	unsigned int size;
	int getKey_Primary(std::string& in_name);
	int getKey_Secondary(std::string& in_name);
private:
};

//---------HASHTABLE---------//
//Fair warning - if you look at this page long enough you will invariably start reading 'HashTable' as 'HashTag.' Which is, of course, unfortunate.
//can I template<class T> this hashtable to ditch hashtable_secondary? I have no idea. I don't think this is the right place for it
template<class T> class HashTable {
public:
	HashTable();
	HashTable(int& in_size);
	~HashTable();

	void printInventory();
	unsigned int get_size();
	bool is_empty();

	//template<typename K>
	T* operator[](int key) {
		return hashTable[key];
	}
	T** hashTable;
protected:
	int getKey_Primary(std::string& in_name);
	int getKey_Secondary(std::string& in_name);
	unsigned int size;

private:
	//double pointer to signify that hashTable will instanciate pointers rather than a block of memory
	//Mountain** hashTable;
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

//---------HASHMAP---------//
class HashMap : /*public HashTable_Perfect<HashTable<Mountain>>,*/ public Graph {
public:
	HashMap();
	~HashMap();

	template<class T/*, typename K*/>
	HashTable_Perfect<T>* operator[](int key) {
		return hashTable[key];
	};

	void insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew);
	void deleteMountain(std::string& in_name);
	
	Mountain* findMountain(std::string& in_name);

protected:
private:
	HashTable_Perfect<HashTable<Mountain>>** hashTable;
	std::vector<Edge*> edge;
	std::vector<Mountain*> range;	//vertices
};

#endif //MOUNTAIN_H