//NOTE: THIS IS GOING TO BE BROKEN FOR A VERY LONG TIME
//This is essentially a copy-paste from assignemnt 8 with almost no variation until I rewrite all of the functions
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<math.h>
#include"HashMap.h"

//EDGE
//Edge::Edge() {
//
//}

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
	distance = 999999999;
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
	distance = 999999999;
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

//
//HashTable
//
HashTable::HashTable() {
	subSize = 0;
	hashTable = new Mountain*[17];
	for (unsigned int i = 0; i < 17; i++) {
		hashTable[i] = nullptr;
	}
}
HashTable::~HashTable() {
	delete[]hashTable;
}

void HashTable::printContents(int index) {
	if (subSize == 0) {
		return;			//really it should have thrown an error, but that can be added later
	}
	for (unsigned int i = 0; i < 17; i++) {
		if (hashTable[i] == nullptr)
			continue;
		std::cout << "(" << index << "," << i << ") :"
			<< hashTable[i]->rank << ":" << hashTable[i]->name << ":" << hashTable[i]->elevation << ":"
			<< hashTable[i]->coordinates.latitude << " " << hashTable[i]->coordinates.N_S << ","
			<< hashTable[i]->coordinates.latitude << " " << hashTable[i]->coordinates.E_W << std::endl;
	}
}
//
//HashTable_Perfect
//
HashTable_Perfect::HashTable_Perfect() {
	size = 0;
	hashTable = new HashTable*[4];
}

HashTable_Perfect::~HashTable_Perfect() {
	delete[]hashTable;
}

void HashTable_Perfect::printContents() {
	if (size == 0) {
		std::cout << "empty" << std::endl;	//I'm only tolerating a print in this function because it is a print function.
		return;								//really it should have thrown an error, but that can be added later
	}
	for (int i = 0; i < 4; i++)
		hashTable[i]->printContents(i);		//calls HashTable's print function, not to be confused with HT_Perfect's
}

Keys HashTable_Perfect::populateKeys(std::string& in_name) {
	Keys k;
	int sum = 0;
	for (unsigned int i = 0; i < in_name.size(); i++)
		sum += in_name[i];

	k.key[0] = sum % 4;
	k.key[1] = k.key[0] % 17;

	return k;
};

//
//HASHMAP
//
HashMap::HashMap() {}
HashMap::~HashMap() {}

void HashMap::insertMountain(int& in_rank, std::string& in_name, double& in_elevation, std::string& in_range, double& in_lat, char& ns, double& in_long, char& ew) {
	Mountain* mountain = new Mountain(in_rank, in_name, in_elevation, in_range, in_lat, ns, in_long, ew);
	Keys k = populateKeys(in_name);
	hashTable[1]->hashTable[1] = mountain;	//make sure this works. Pointers, man.
	vertices.push_back(mountain);	//add to graph
	size++;
}


void HashMap::deleteMountain(std::string& in_name) {
	Keys k = populateKeys(in_name);
	if (hashTable[k[1]]->hashTable[k[2]] != nullptr) {	//make sure there is actually somehting there before trying to delete
		delete this->hashTable[k[1]]->hashTable[k[2]];
		size--;
	}
}

bool HashMap::mountainExists(Keys& lookup) {
	return !(this->hashTable[lookup[0]]->hashTable[lookup[1]] == nullptr);
}

Mountain* HashMap::findMountain(std::string& in_name) {
	Keys k = populateKeys(in_name);
	return this->hashTable[k[0]]->hashTable[k[1]];
}

//this version of addEdge calculates the difference in the coordinates.
void HashMap::addEdge(Keys& origin, Keys& destination) {
	//technically, this will fail for mountains in different hemispheres, since it does not check for N/S|E/W pairs.
	//but technically I dont have neough time and will come back to it later. Probably in the dev branch again

	double weight = -1;
	//this line just finds the difference between the two mountains in the x-plane. Will need to pythag. later.
	double diff_x = (this->hashTable[origin[0]]->hashTable[origin[1]]->coordinates.longitude - this->hashTable[destination[0]]->hashTable[destination[1]]->coordinates.longitude);
	//same as above but for y
	double diff_y = (this->hashTable[origin[0]]->hashTable[origin[1]]->coordinates.latitude - this->hashTable[destination[0]]->hashTable[destination[1]]->coordinates.latitude);

	//use pythag. to compute the distance between. Technically, trig could have been used, but since all values are known, it's not much different.
	weight = sqrt((pow(diff_x, 2)) + (pow(diff_y, 2)));	//weight = the squart root of the sum of the differences squared.

	Edge* new_edge = new Edge(this->hashTable[destination[0]]->hashTable[destination[1]], weight);
	this->hashTable[origin[0]]->hashTable[origin[1]]->edge.push_back(new_edge);
}

void HashMap::addEdge(Keys& origin, Keys& destination, double& weight) {
	Edge* new_edge = new Edge(this->hashTable[destination[0]]->hashTable[destination[1]], weight);
	this->hashTable[origin[0]]->hashTable[origin[1]]->edge.push_back(new_edge);
}

Mountain* HashMap::shortestPath(std::string& origin, std::string& destination) {
	//hash out the locations of the begin/end
	Keys start = populateKeys(origin);
	Keys end = populateKeys(destination);
	Mountain* current = this->hashTable[start[0]]->hashTable[start[1]];
	Mountain* fin = this->hashTable[end[0]]->hashTable[end[1]];

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

	if (current->edge.size() < 1) {
		std::cout << " Please build the edges before traversing." << std::endl;
		return nullptr;
	}
	//set the algorithm conditions.
	//Although the constructors set these by default, if the algorithm is run again in the same run-through, it will have the old values in it.
	for (std::vector<Mountain*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		(*it)->distance = 9999999;
		(*it)->previous = nullptr;
		(*it)->have_visited = false;
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

	return fin;	//this stores the distance as an integer in 'distance', which can be accessed in main()
}

//my one true hate. Dijkastraartighjasdfg-pronunciation.
Mountain* HashMap::shotestDistance(std::string& origin, std::string& destination) {
	//hash out the locations of the begin/end
	Keys start = populateKeys(origin);
	Keys end = populateKeys(destination);
	Mountain* current = this->hashTable[start[0]]->hashTable[start[1]];
	Mountain* fin = this->hashTable[end[0]]->hashTable[end[1]];

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

	if (current->edge.size() < 1 || fin->edge.size() < 1) {
		std::cout << " Please build the edges before traversing." << std::endl;
		return nullptr;
	}
	//set the algorithm conditions.
	//Although the constructors set these by default, if the algorithm is run again in the same run-through, it will have the old values in it.
	for (std::vector<Mountain*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
		(*it)->distance = 9999999;	//efectively double_max
		(*it)->previous = nullptr;
		(*it)->have_visited = false;
	}
	std::vector<Mountain*> solved;
	current->have_visited = true;
	current->distance = 0;
	solved.push_back(current);


	while (!fin->have_visited) {
		double minDistance = 9999999;
		Mountain* minMountain = nullptr, * prevMountain = nullptr;
		for (std::vector<Mountain*>::iterator it = solved.begin(); it != solved.end(); it++) {
			current = (*it);
			for (std::vector<Edge*>::iterator jt = (*it)->edge.begin(); jt != (*it)->edge.end(); jt++) {
				if (!(*jt)->next->have_visited) {
					double dist = current->distance + (*jt)->weight;	//could has just as easily been "(*it)->distance + (*jt)->weight;" In fact, current is largely syntax sugar
					if (minDistance > dist) {
						minDistance = dist;
						minMountain = (*jt)->next;
						prevMountain = current;
					}
				}
			}
		}
		minMountain->distance = minDistance;
		minMountain->previous = prevMountain;
		minMountain->have_visited = true;
		solved.push_back(minMountain);
	}

	return fin;	//reverse the path this left to find distance/path/etc.
}