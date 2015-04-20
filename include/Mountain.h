#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include"Graph.h"
#include"HashTable.h"

class Mountain;

struct Edge {
	//construct/destruct
	Edge();
	Edge(Mountain*, int&);
	~Edge();

	Mountain* v;
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
#endif