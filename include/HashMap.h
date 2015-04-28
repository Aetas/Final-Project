#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include<string>
#include<vector>

/*
WIP naming conventions
	If it is an attribute of an object, and underscore is used to denote object-attribute relation <object>_<attribute> is used. 
	If it is a method or unique attribute, no underscore is used and caps denote words.
	Whole words are prefered over abbreviations
	Caps are used in object declarations so a mountain can be declared as Mountain* mountain = new Mountain();
*/


//Since inheritance is used, this is largely to keep the compiler happy
//The classes/structs are listed in the order they appear as a way to keep track of them
class Edge;
class Mountain;
class Graph;
class HashTable_Perfect;
class HashTable;
class HashMap;

//It was ugly and hard to keep track of passing pointers to integer arrays around to hold keys
//so I made this struct to simplify things, though it might not seem like it.
//the template is to support nesting to any degree, as it makes as many keys as specific.
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
	Edge();
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
class Graph {
public:
	//construct/destruct
	Graph();
	~Graph();

	//by name
	virtual Mountain* shortestPath(std::string&, std::string&) = 0;		//returns a mountain because it is used for trace-back via previous attribute.
	virtual Mountain* shotestDistance(std::string& origin, std::string& destination) = 0;	//same as above. And below
	virtual void addEdge(Keys& origin, Keys& destination, double& weight) = 0;	//pure vitrual, graph itself does not actually have access to what it needs. (Which is the hashTable lookup)
	void displayEdges(Mountain*);
	void BFTraversal();

protected:
	void reset_visited();	//protected because why not
	std::vector<Mountain*> vertices;
private:
};

//---------HASHTABLE_PERFECT---------//
/*template<class T>*/ class HashTable_Perfect {
public:
	HashTable_Perfect();
	~HashTable_Perfect();

	inline unsigned int size_of() {
		return size;
	}

	inline bool is_empty() {
		return (size == 0);
	}

	void printContents();

	Mountain* getMountain(std::string& in_name);	//return mountian by name
	Mountain* getMountain(Keys& k);					//return mountain by key

	Keys populateKeys(std::string& in_name);

	template<typename K>
	HashTable* operator[](K key) {
		return this->hashTable[key];
	}
	
protected:
	HashTable* hashTable[5];
	unsigned int size;		//this will be the overall/total size. Thus inherited into HashMap
private:
};

//HASHTABLE
class HashTable {
public:
	HashTable();
	~HashTable();

	inline unsigned int size_of() {
		return subSize;
	}

	inline bool is_empty() {
		return (subSize == 0);
	}

	void printContents(int index);

	template<typename K>
	Mountain* operator[](K key) {
		return this->hashTable_Secondary[key];
	}

	//friend ostream&<<(os&, HashMap*)	//add later, no time now
										//also add one for Mountain for when [][]is up and running

	unsigned int subSize;
	Mountain* hashTable_Secondary[17];
protected:
private:
};

//---------HASHMAP---------//
//to template... or not to template...
//I'm removing the template bit for now because the descision is hindering progress. I can always come back and convert/paste in templates if I need to.
//template<class T>
class HashMap : public HashTable_Perfect, public Graph {
public:
	HashMap();
	~HashMap();

	void insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew);
	void deleteMountain(std::string& in_name);
	void addEdge(Keys& origin, Keys& destination);
	void addEdge(Keys& origin, Keys& destination, double& weight);

	//I thought about making a version of this that takes a string argument but the idea would be to avoid generating keys.
	//However, since the first thing that would happen in a string-argument version would be to generate the keys, it really achieved nothing.
	//The only real difference is that they keys are made in main() before calling it, or made in the function after calling it.
	//on top of that, if it returns true, then I need the keys in main() anyhow.
	bool mountainExists(Keys& lookup);
	//I lied above. I want to make sure the names match.
	bool mountainExists(Keys& lookup, std::string& match_name);
	//to check for collision. Really just a debugging utillity
	bool is_occupied(Keys& k);

	Mountain* shortestPath(std::string&, std::string&);		//returns a mountain because it is used for trace-back via previous attribute.
															//required overload in HashMap because of the hash-lookup
	Mountain* shotestDistance(std::string& origin, std::string& destination);
protected:
private:
};

#endif //MOUNTAIN_H
