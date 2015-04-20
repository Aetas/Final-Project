#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#define PRIMARY_SIZE 10
#define SECONDARY_SIZE 10

#include<string>
#include<vector>

//Since inheritance is used, making the compiler happy is needed
//The classes are listed in the order they appear as a way to keep track of them
class Mountain;
class ActionJesus;
class HashTable_Primary;
class HashTable_Secondary;
class Graph_Primary;
class Graph_Secondary;

struct Edge {
	//construct/destruct
	Edge() {
		next = nullptr;
		weight = -1;
	};

	Edge(Mountain* destination, int& in_weight) {
		next = destination;
	};

	~Edge() {
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

	bool have_visited;
	int distance;

protected:
private:
	Mountain* previous;

	std::string name;
	double elevation;
	std::vector<Edge*> edge;
};

//grandaddy class. Basically just used to easily pass information between graphs and hash tables
class ActionJesus {
public:

protected:

private:
	HashTable_Primary hash;
	Graph_Primary graph;
};

//Fair warning - if you look at this page long enough you will invariably start reading 'HashTable' as 'HashTag.' Which is of course, unfortunate.
class HashTable_Primary {
public:
	HashTable_Primary();
	HashTable_Primary(int& in_size);
	~HashTable_Primary();

	void printInventory();
	void insertMountain(std::string& in_name, double& in_elevation);//name, elevation
	void deleteMountain(std::string& in_name);						//name
	void collision_resolution(std::string& in_name, double& in_elevation, int& key);	//name, year, key
	Mountain* findMountain(std::string& name);						//name

	unsigned int get_size();
	bool is_empty();
protected:
	int get_hash_key(std::string&);

private:
	int size;
	//pointer to pointers for secondary hash table which represents the range that the mountains are found in
	HashTable_Secondary** hashTable_Range;	//figure out the hash functions, revisit naming convention	

};

class HashTable_Secondary : public HashTable_Primary {
public:
	HashTable_Secondary();
	HashTable_Secondary(int& in_size);
	~HashTable_Secondary();
protected:

private:
	Mountain** hashTable_Mountain;
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
	Mountain* shortestDistance(std::string&, std::string&);	//return destination-Vertex?  || dijkastra's

protected:
	void reset_visited();	//protected because why not

private:
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
protected:

private:
	std::string rangeName;

	std::vector<Edge*> edge;
	std::vector<Mountain*> mountain;	//secondary vertices WRT primary
};

#endif //MOUNTAIN_H