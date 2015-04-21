#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#define PRIMARY_SIZE 10
#define SECONDARY_SIZE 10

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
//The classes are listed in the order they appear as a way to keep track of them
class ActionJesus;
class Mountain;
class HashTable_Primary;
class HashTable_Secondary;
class Graph_Primary;
class Graph_Secondary;

//in general, naming conventions could have been more clear from the start. It's been more work than it's worth to convert old things to new conventions


//grandaddy class. Basically just used to easily pass information between graphs and hash tables
//Name is still up in the air, as one might imagine
class ActionJesus {
public:
	HashTable_Primary hash;
	Graph_Primary graph;
	//virtual add_mountain	(?)		//inherit both and override so that I do not have to call add a million times to update both hash and graph
	//virtual remove_mountain (?)	//
protected:
private:
};

//Are two edge types needed?
//The reason a second would be needed is to link ranges. Now if I don't plan on traversing ranges, then this is slightly useless.
//However, if I don't plan on using the range graph, then what's the point of using a graph structure?
//Probs need Edge_Mountain and Edge_Range. Molto bene.
//EDGE
struct Edge_Range {
	//construct/destruct
	Edge_Range() {
		next = nullptr;
		weight = -1;
	};

	Edge_Range(Mountain* destination, int& in_weight) {
		next = destination;
	};

	~Edge_Range() {
		if (next != nullptr)
			delete next;
	};

	Mountain* next;
	int weight;
};

struct Edge_Mountain {
	//construct/destruct
	Edge_Mountain() {
		next = nullptr;
		weight = -1;
	};

	Edge_Mountain(Mountain* destination, int& in_weight) {
		next = destination;
	};

	~Edge_Mountain() {
		if (next != nullptr)
			delete next;
	};

	Mountain* next;
	int weight;
};

//vertex in the graph sense, node in the hash table sense
class Mountain {
public:
	//construct/destruct
	Mountain();
	Mountain(std::string&);	//make with name
	~Mountain();

	bool have_visited;		//record keeping
	int distance;			//record keeping for algs

protected:
private:
	//used for tracing paths in route finding algorithms
	Mountain* previous;

	struct Coordinates {
		char N_S, E_W;
		double latitude, longitude;
	} coordinates;

	std::string name;
	double elevation;
	std::vector<Edge_Mountain*> edge;
};

//Fair warning - if you look at this page long enough you will invariably start reading 'HashTable' as 'HashTag.' Which is, of course, unfortunate.
class HashTable_Primary {
public:
	HashTable_Primary();
	HashTable_Primary(int& in_size);
	~HashTable_Primary();

	void printInventory();
	void insertMountain(std::string& in_name, double& in_elevation);//name, elevation
	void deleteMountain(std::string& in_name);						//name
	void collision_resolution(std::string& in_name, double& in_elevation, int& key);	//name, year, key
	Mountain* findMountain(std::string& name);						//this will most likely never be used. Ever. The whole idea is to find graph vertices with hash tables.

	unsigned int get_size();
	bool is_empty();
protected:
	int get_hash_key(std::string&);

private:
	int size;
	//pointer to pointers for secondary hash table which represents the range that the mountains are found in
	HashTable_Secondary** hashTable;	//figure out the hash functions, revisit naming convention	

};

class HashTable_Secondary : public HashTable_Primary {
public:
	HashTable_Secondary();
	HashTable_Secondary(int& in_size);
	~HashTable_Secondary();
protected:

private:
	Mountain** hashTable;
};

//writing traversal algorithms is going to be a f**king nightmare.
//but that's fine.
class Graph_Primary {
public:
	//construct/destruct
	Graph_Primary();
	~Graph_Primary();

	//by name
	void addEdge(int&, int&, int);	//v1, v2, weight
	void addMountain(std::string&);	//name
	void printRange();
	void displayEdges(Mountain*);
	void BFTraversal();
	void BFTraversal(std::string&);
	Mountain* shortestPath(std::string&, std::string&);		//

protected:
	void reset_visited();	//protected because why not

private:
	std::vector<Edge_Range*> Prim_edge;
	std::vector<Graph_Secondary*> range;	//vertices

};

//since graph_secondary has to function as both a graph root and a vertex, it has some added baggage between graph_primary (through inheritance), and the attribute of a range (name)
//I chose to store the range name largely because memory is something I have in abundance, and it is the same for all mountains in the range (obviously)
//This meant that I can get away with one more layer of abstraction.
class Graph_Secondary : public Graph_Primary {
public:
	Graph_Secondary();
	~Graph_Secondary();
	void addEdge();
		//shortest distance is only really applicable to mountain to mountain, since ranges are so large there's no appreciable way to represent distances between two
	Mountain* shortestDistance(std::string&, std::string&);	//return destination-Vertex?  || dijkastra's
protected:

private:
	std::string rangeName;

	std::vector<Edge_Mountain*> edge;
	std::vector<Mountain*> mountain;	//secondary vertices WRT primary
};

#endif //MOUNTAIN_H