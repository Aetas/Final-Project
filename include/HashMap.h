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
//SIDE PROJECT -- TRYING TO SEE IF I CAN TEMPLATE A HASHTABLE CLASS
//CAPSLOCK IS CRUISE CONTROLL FOR COOL.
template<class T> class HashTable_Perfect {
public:
	HashTable_Perfect() {};
	HashTable_Perfect(int& in_size) {};
	~HashTable_Perfect() {};

	void printInventory();
	unsigned int get_size();
	bool is_empty();

	template<typename K>
	T* operator[](K key) {
		return (this->hashTable[key]);
	}
	T** hashTable;
protected:
	unsigned int size;
	int getKey_Primary(std::string& in_name);
	int getKey_Secondary(std::string& in_name);
private:
};

//---------HASHMAP---------//
template<class T>
class HashMap : public HashTable_Perfect<T>, public Graph {
public:
	HashMap() {};
	~HashMap() {};

	template<typename K>
	HashTable_Perfect<HashTable_Perfect<Mountain>>* operator[](K key) {
		return hashTable[key];
	};

	void insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew);
	void deleteMountain(std::string& in_name);
	
	Mountain* findMountain(std::string& in_name);

protected:
private:
	HashTable_Perfect<T>** hashTable;
	std::vector<Edge*> edge;
	std::vector<Mountain*> range;	//vertices
};

#endif //MOUNTAIN_H