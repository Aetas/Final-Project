//NOTE: THIS IS GOING TO BE BROKEN FOR A VERY LONG TIME
//This is essentially a copy-paste from assignemnt 8 with almost no variation until I rewrite all of the functions
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include"HashMap.h"

//EDGE
Edge::Edge() {

}

Edge::Edge(Mountain* destination, double& in_weight) {
	next = destination;
}

Edge::~Edge() {
	if (next != nullptr)
		delete next;
}


//MOUNTAIN
Mountain::Mountain(std::string& in_name) {
	//If there is no name, there is no need to make a mountain
	//this is the closest thing to a default constructor that Mountain will get.
	// -1 means no value passed
	rank = -1;
	name = in_name;
	elevation = -1;
	range = "none assigned";
	coordinates.latitude = -1;
	coordinates.N_S = ' ';
	coordinates.latitude = -1;
	coordinates.E_W = ' ';
	have_visited = false;
	distance = MAX_DISTANCE;
}

Mountain::Mountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& NS, double& in_long, char& EW) {
	//Clean-cut assignment
	rank = in_rank;
	name = in_name;
	elevation = in_elevation;
	range = in_range;
	coordinates.latitude = in_lat;
	coordinates.N_S = NS;
	coordinates.latitude = in_long;
	coordinates.E_W = EW;
	have_visited = false;
	distance = MAX_DISTANCE;
}

Mountain::~Mountain() {}


Graph::Graph() {

}

Graph::~Graph() {

}

void Graph::reset_visited() {	//resets the visited tracker for traversal algorithms
	for (std::vector<Mountain*>::iterator it = vertices.begin(); it != vertices.end(); it++) {
		(*it)->have_visited = false;
	}
}
void Graph::displayEdges(Mountain* mountain) {
	if (mountain->edge.size() > 0) {
		//this print line is sepparate from the loop below because it follows a different print style that I kept from assignment 8
		std::cout << mountain->edge[0]->next->name;
		for (std::vector<Edge*>::iterator it = mountain->edge.begin() + 1; it != mountain->edge.end(); it++) {
			std::cout << "***" << (*it)->next->name;
		}
	}
}
void Graph::BFTraversal() {
	Mountain* current = vertices[0];

	std::queue<Mountain*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty()) {
		current = q.front();
		q.pop();
		for (unsigned int i = 0; i < current->edge.size(); i++) {
			if (!current->edge[i]->next->have_visited) { //if the edge has not been visited...
				current->edge[i]->next->have_visited = true;
				std::cout << current->edge[i]->next->name << std::endl;
				q.push(current->edge[i]->next);
			}
		}
	}
	reset_visited();	//return to default condition before exit
}

//I'm not sure this function actually has a use. I mean, it probably does, but when the hell would I use it? Probs going to be deleted
//another mark against this is that graph does not have access to hash lookup, and I don't want to loop this biotch to O(n).
//meaning I would then have to go to a HashMap implemintation w/ pure virtual in Graph.
//Which technically is fine, but it is ugly maintenance
void Graph::BFTraversal(std::string& start_Mountain) {

}

//HASHMAP
HashMap::HashMap() {
	hashTable = new HashTable_Perfect<HashTable_Perfect<Mountain>>*[4];
	for (unsigned int i = 0; i < 4; i++) {
		hashTable[i] = nullptr;
	}
}

HashMap::~HashMap() {
	if (size > 0)
		delete[]hashTable;
}


void HashMap::insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew) {
	Mountain* mountain = new Mountain(in_rank, in_name, in_elevation, in_range, in_lat, ns, in_long, ew);
	Keys<2> k = populateKeys(in_name);
	*this[k[0]][k[1]] = *mountain;	//make sure this works. Pointers, man.
	vertices.push_back(mountain);	//add to graph
	size++;
}


void HashMap::deleteMountain(std::string& in_name) {
	Keys<2> k = populateKeys(in_name);
	if (this[k[1]][k[2]] != nullptr) {	//make sure there is actually somehting there before trying to delete
		delete this[k[1]][k[2]];
		size--;
	}
}

Mountain* HashMap::findMountain(std::string& in_name) {
	Keys<2> k = this->populateKeys(in_name);
	return this[k[0]][k[1]];
}

void HashMap::addEdge(Keys<2>& origin, Keys<2>& destination, double& weight) {
	Edge* new_edge = new Edge(this[destination[0]][destination[1]], weight);
	this[origin[0]][origin[1]]->edge.push_back(new_edge);
}

//my one true hate. Dijkastraartighjasdfg-pronunciation.
Mountain* HashMap::shortestPath(std::string& origin, std::string& destination) {
	//hash out the locations of the begin/end
	Keys<2> start = populateKeys(origin);
	Keys<2> end = populateKeys(destination);
	Mountain* current = this[start[0]][start[1]];
	Mountain* fin = this[end[0]][end[1]];

	if (current == nullptr) {
		std::cout << " The origin mountain does not exist." << std::endl;
		return nullptr;
	}
	if (fin == nullptr) {
		std::cout << " The destination mountain does not exist." << std::endl;
		return nullptr;
	}
	//if it is possible to traverse...
	if (current->range != fin->range) {
		std::cout << " These mountains are in different ranges." << std::endl;
		return nullptr;
	}

	//set the algorithm conditions.
	//Although the constructors set these by default, if the algorithm is run again in the same run-through, it will have the old values in it.
	for (std::vector<Mountain*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		(*it)->distance = 99999;
		(*it)->previous = nullptr;
	}

	std::queue<Mountain*> path;
	std::queue<Mountain*> q;

	current->have_visited = true;
	current->distance = 0;
	q.push(current);
	path.push(current);	//path starts at the beginning... which is 'current' presently
	
	while (!q.empty()) {
		current = q.front();
		q.pop();
		for (std::vector<Edge*>::iterator it = current->edge.begin(); it != current->edge.end(); it++) {
			if (!(*it)->next->have_visited) {
				(*it)->next->distance = current->distance + 1;
				(*it)->next->previous = current;
				q.push((*it)->next);
			}
		}
		current->have_visited = true;
	}

	return fin;
}