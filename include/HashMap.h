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

//It was ugly and hard to keep track of passing pointers to integer arrays around to hold keys
//so I made this struct to simplify things, though it might not seem like it.
//the template is to support nesting to any degree, as it makes as many keys as specifiec.
//Unfortunately, my keygen function now falls short of it's key container
struct Keys {
	Keys(){};
	~Keys(){};
	unsigned int key[2];
	void operator=(const Keys& in_key) {
		key[0] = in_key.key[0];
		key[1] = in_key.key[1];
	}
	unsigned int& operator[](int k) {
		return key[k];
	}
};

//---------EDGE---------//
//This became a class out of chance. Largely because I had the construct/destruct inlined, 
//but it needed a complete mountain type to call delete on. So now not so much
class Edge {
public:
	//construct/destruct
	Edge() {};
	Edge(Mountain* destination, double& in_weight);
	~Edge();

	Mountain* next;
	double weight;
};

//---------MOUNTAIN---------//
//vertex in the graph sense, node in the hash table sense
//I ditched protected and private in favor of not writing so many get/set methods as mountain is already so protected from it's location in the higher level strcture.
//Which means that a struct would be identical to this in every way. But whatever. Headerfile conventions are too goddamn tangled.
class Mountain {
public:
	//construct/destruct
	Mountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& NS, double& in_long, char& EW);
	Mountain(std::string&);	//make with name
	~Mountain();

	bool have_visited;		//record keeping
	double distance;		//record keeping for algs

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
	virtual Mountain* shortestPath(std::string&, std::string&) = 0;		//returns a mountain because it is used for trace-back via previous attribute.
	virtual void addEdge(Keys& origin, Keys& destination, double& weight) = 0;	//pure vitrual, graph itself does not actually have access to what it needs. (Which is the hashTable lookup)
	void displayEdges(Mountain*);
	void BFTraversal();
	void BFTraversal(std::string&);

protected:
	void reset_visited();	//protected because why not
	std::vector<Mountain*> vertices;
private:
};

class HashTable {
public:
	HashTable() {};
	~HashTable() {};

	void printContents();

	unsigned int size_of();
	bool is_empty();

	Keys populateKeys(std::string& in_name) {
		Keys k;
		int sum = 0;
		for (unsigned int i = 0; i < in_name.size(); i++)
			sum += in_name[i];

		k.key[0] = sum % 4;
		k.key[1] = k.key[0] % 17;

		return k;
	};

	template<typename T>
	T* operator[](unsigned int key) {
		return hashTable[key];
	}
	
protected:
	HashTable_Perfect<Mountain>** hashTable;
	unsigned int size;
private:
	//Mountain** hashTable;
};

//---------HASHTABLE_PERFECT---------//
//perfect hashtable w/ templates
template<class T> class HashTable_Perfect : public HashTable {
public:
	HashTable_Perfect() {
		size = 0;
		hashTable = new T*[SECONDARY_SIZE];
		//for (unsigned int i = 0; i < SECONDARY_SIZE; i++)
		//	hashTable[i] = nullptr;
	}
	HashTable_Perfect(int s_size) {		//specify size of second table, likely never used since arrays cant be given constructor arguments
		size = 0;
		hashtable = new T*[s_size];
	}
	~HashTable_Perfect() {
		if (size > 0)
			delete[]hashTable;
	}
	template<typename K>
	T* operator[](unsigned int key) {
		return this->hashTable[key];
	}

	T** hashTable;
protected:
	unsigned int size;
private:
	//T** hashTable;
};

//---------HASHMAP---------//
//to template... or not to template...
//I'm removing the template bit for now because the descision is hindering progress. I can always come back and convert/paste in templates if I need to.
//template<class T>
class HashMap : public HashTable, public Graph {
public:
	HashMap();
	~HashMap();

	void insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew);
	void deleteMountain(std::string& in_name);
	void addEdge(Keys& origin, Keys& destination, double& weight);

	Mountain* findMountain(std::string& in_name);
	Mountain* shortestPath(std::string&, std::string&);		//returns a mountain because it is used for trace-back via previous attribute.
	//required overload in HashMap because of the hash-lookup
	template<class T>
	T* operator[](unsigned int key) {
		return hashTable[key];
	}
	
protected:
private:
	//just kidding, it was already broken
	//HashTable_Perfect<HashTable_Perfect<Mountain>>** hashTable;
};

#endif //MOUNTAIN_H

/*void printContents() {
if (size == 0) {
std::cout << "empty" << std::endl;	//I'm only tolerating a print in this function because it is a print function.
return;								//really it should have thrown an error, but that can be added later
}
for (int i = 0; i < H_TABLE_SIZE; i++) {
if (hashTable[i] == nullptr)
continue;	//skip rest
std::cout << hashTable[i]->title << ":" << hashTable[i]->year << std::endl;
}
}
inline unsigned int size_of() {
return size;
}
inline bool is_empty() {
return (size == 0);
}
template<typename K>
T* operator[](K key) {
return hashTable[key];
}

//I'll come back top this later when it can determine it's own size
//though it might be easiest to just have keys templated with the nesting depth specified at construction
Keys<2> populateKeys(std::string& in_name) {
Keys<2> k;
int sum = 0;
for (unsigned int i = 0; i < in_name.size(); i++)
sum += in_name[i];
k.key[0] = sum % PRIMARY_SIZE;
k.key[1] = k.key[0] % SECONDARY_SIZE;
return k;
}*/
