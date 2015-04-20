//NOTE: THIS IS GOING TO BE BROKEN FOR A VERY LONG TIME
//This is essentially a copy-paste from assignemnt 8 with almost no variation until I rewrite all of the functions
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include"Mountain.h"

HashTable_Primary::HashTable_Primary()
{
	size = 0;
	hashTable = new Mountain*[PRIMARY_SIZE];
	for (int i = 0; i < PRIMARY_SIZE; i++)
		hashTable[i] = nullptr;
}

HashTable_Primary::HashTable_Primary(int& table_size)
{
	size = 0;
	hashTable = new Mountain*[table_size];
	for (int i = 0; i < table_size; i++)
		hashTable[i] = nullptr;
}

HashTable_Primary::~HashTable_Primary()
{
	delete[]hashTable;
}

void HashTable_Primary::printInventory()
{
	if (size == 0)	//nothing in dood-ma-bob
	{
		std::cout << "empty" << std::endl;	//I'm only tolerating a print in this function because it is a print function.
		return;
	}
	for (int i = 0; i < H_TABLE_SIZE; i++)
	{
		if (hashTable[i] == nullptr)
			continue;	//skip rest
		std::cout << hashTable[i]->title << ":" << hashTable[i]->year << std::endl;
		if (hashTable[i]->next != nullptr)	//I wanted to do this after the initial cout because I don't want to allocate from the heap in the majority of cases.
		{
			Movie* temp = hashTable[i]->next;
			while (temp != nullptr)			//traverse the linked list
			{
				std::cout << temp->title << ":" << temp->year << std::endl;
				temp = temp->next;
			}
		}
	}
}

void HashTable_Primary::insertMovie(std::string& in_title, int& in_year)
{
	int key = get_hash_key(in_title);
	if (hashTable[key] != nullptr)
		collision_resolution(in_title, in_year, key);
	else
	{
		Movie* temp = new Movie(in_title, in_year, key);
		hashTable[key] = temp;
	}
	size++;
}

void HashTable_Primary::deleteMovie(std::string& in_title)
{

	int key = get_hash_key(in_title);

	if (hashTable[key]->title == in_title && hashTable[key]->next == nullptr)
	{
		delete hashTable[key];
		hashTable[key] = nullptr;
		size--;
		return;
	}

	Movie* it = hashTable[key];
	Movie* prev = it;
	Movie* del = nullptr;

	while (del == nullptr)
	{
		if (it->title == in_title)
		{
			del = it;
			prev->next = del->next;
			delete del;
			size--;
			return;
		}
		prev = it;
		it = it->next;
	}

	size--;
}

void HashTable_Primary::collision_resolution(std::string& in_title, int& in_year, int& key)
{
	Movie* new_movie = new Movie(in_title, in_year, key);
	Movie* it = hashTable[key];
	Movie* prev = it;
	if (new_movie->title.compare(hashTable[key]->title) < 0)	//if it is before the first entry...
	{
		new_movie->next = hashTable[key];
		hashTable[key] = new_movie;
		return;
	}
	it = it->next;
	while (it != nullptr)
	{
		if (new_movie->title.compare(it->title) < 0)
		{
			new_movie->next = it;
			prev->next = new_movie;
			return;
		}
		prev = it;
		it = it->next;
	}
	prev->next = new_movie;	//if it has not returned yet, make it the last of the chain
}

Movie* HashTable_Primary::findMovie(std::string& in_title)
{
	int key = get_hash_key(in_title);
	//case 1
	if (hashTable[key] == nullptr)	//if there is no movie in the index, nothing there, return nullptr for main() to handle
		return nullptr;
	Movie* ans = hashTable[key];	//else handle case 2 & 3
	if (hashTable[key]->title != in_title)
	while ((ans != nullptr) && (ans->title != in_title))	//also takes care of the case where the index is taken, but the movie does not exist
		ans = ans->next;

	return ans;	//at this point, ans either holds the answer the function call came for, or nullptr, which is the default case for not found
}

unsigned int HashTable_Primary::get_size()
{
	return size;
}

bool HashTable_Primary::is_empty()
{
	if (size > 0)
		return false;
	return true;
}

int HashTable_Primary::get_hash_key(std::string& in_title)
{
	int sum = 0;
	for (std::string::iterator it = in_title.begin(); it != in_title.end(); it++)
		sum += *it;	//sum ASCII

	return (sum % 10/*H_TABLE_SIZE*/);	//at this point, I've forgone the idea of adding extra baggage to let user redefine the size, 
	//because that happens before the compiler runs anyhow, so changing the macro is just as easy, if not easier
	//the other option is table_size, which would hold the table size passed to the constructor just for hash key use
	//the main reason I cared about a simple 8 bytes floating around my class is not because of the space, but because
	//unsigned int would be the correct choice (*one of many) for holding a size, while plain int would be plain stupid.
	//the reason being, is that the entire idea of giving a choice of table size from runtime is that the user could use it for any size
	//and any size is a rather large number. So rather than a hack job, I chose to cut the weight and use a compiler macro for that silky smooth action. nns.
}

Graph_Primary::Graph_Primary()
{

}

Graph_Primary::~Graph_Primary()
{

}

void Graph_Primary::addEdge(int& key_o, int& key_d, int weight)
{
	Edge* new_edge = new Edge(range[key_d], weight);	//make the edge
	range[key_o]->edge.push_back(new_edge);			//add to vector
}

void Graph_Primary::addMountain(std::string& name)
{
	Mountain* new_Mountain = new Mountain(name);
	range.push_back(new_Mountain);
}

void Graph_Primary::printRange()
{
	for (std::vector<Mountain*>::iterator it = range.begin(); it != range.end(); it++)
	{
		std::cout << (*it)->district << ":" << (*it)->name << "-->";
		display_edges(*it);	//optional, functional implementation
		std::cout << std::endl;
	}
}

void Graph_Primary::displayEdges(Mountain* home)
{
	if (home->edge.size() > 0)	//if there is an edge (always is, this is for 'bullet proofing')
	{
		std::cout << home->edge[0]->v->name;	//cout the first name always
		if (home->edge.size() > 1)				//if there is another/more edges, print them in the format.
			for (std::vector<Edge*>::iterator jt = home->edge.begin() + 1; jt != home->edge.end(); jt++)	//do all of them.
				std::cout << "***" << (*jt)->v->name;
	}
}

void Graph_Primary::BFTraversal()
{
	Mountain* current = range[0];	//start at the start? or boulder? writeup sucks.

	std::queue<Mountain*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (unsigned int i = 0; i < current->edge.size(); i++)
		{
			if (current->edge[i]->v->have_visited == false)
			{
				current->edge[i]->v->have_visited = true;
				std::cout << current->edge[i]->v->name << std::endl;
				q.push(current->edge[i]->v);
			}
		}
	}
	reset_visited();
}

void Graph_Primary::BFTraversal(std::string& startingCity)
{
	Mountain* current = nullptr;
	int j = 0;
	std::vector<Mountain*>::iterator jt = range.begin();
	while (current == nullptr)
	{
		if ((*jt)->name == startingCity)
			current = *jt;
		jt++;
	}
	std::queue<Mountain*> q;

	std::cout << current->name << std::endl;
	current->have_visited = true;
	q.push(current);

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();	//remove the oldest to update queue
		for (std::vector<Edge*>::iterator it = current->edge.begin(); it != current->edge.end(); it++)
		{
			if ((*it)->v->have_visited == false)
			{
				(*it)->v->have_visited = true;
				std::cout << (*it)->v->name << std::endl;
				q.push((*it)->v);
			}
		}
	}
	reset_visited();
}

Mountain* Graph_Primary::shortestPath(std::string& o, std::string& d)
{
	Mountain* current = nullptr;
	Mountain* fin = nullptr;

	std::vector<Mountain*>::iterator ft = range.begin();
	while ((current == nullptr || fin == nullptr))	//finds the range associated with the names
	{
		if ((*ft)->name == o)
			current = *ft;
		if ((*ft)->name == d)
			fin = *ft;
		ft++;
		if (ft == range.end())
			break;
	}

	if (current == nullptr || fin == nullptr)
	{
		std::cout << "One or more cities doesn\'t exist" << std::endl;
		return nullptr;
	}
	if (current->district == -1)
	{
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return nullptr;
	}
	if (current->district != fin->district)	//they cannot be reached if they are not connected
	{
		std::cout << "No safe path between cities" << std::endl;
		return nullptr;
	}

	//ensure defaults
	for (std::vector<Mountain*>::iterator it = range.begin(); it != range.end(); it++)
		(*it)->distance = MAX_INT, (*it)->previous = nullptr;

	std::queue<Mountain*> path;
	std::queue<Mountain*> q;

	current->have_visited = true;	//initial
	current->distance = 0;			//no edges.
	q.push(current);
	path.push(current);	//path starts 

	while (!q.empty())
	{
		current = q.front();	//set to oldest
		q.pop();				//remove the oldest to update queue
		for (std::vector<Edge*>::iterator it = current->edge.begin(); it != current->edge.end(); it++)
		{
			if ((*it)->v->have_visited == false)
			{
				//(*it)->v->have_visited = true;
				(*it)->v->distance = current->distance + 1;
				(*it)->v->previous = current;
				q.push((*it)->v);
			}
		}
		current->have_visited = true;
	}
	reset_visited();

	return fin;
}

Mountain* Graph_Primary::shortestDistance(std::string& o, std::string& d)
{
	//Dijakstra's Algorithm
	Mountain* temp = nullptr;
	Mountain* fin = nullptr;

	std::vector<Mountain*>::iterator ft = range.begin();
	while ((temp == nullptr || fin == nullptr))	//finds the range associated with the names
	{
		if ((*ft)->name == o)
			temp = *ft;
		if ((*ft)->name == d)
			fin = *ft;
		ft++;
		if (ft == range.end())
			break;
	}
	if (temp == nullptr || fin == nullptr)
	{
		std::cout << "One or more cities doesn\'t exist" << std::endl;
		return nullptr;
	}
	if (temp->district == -1)
	{
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return nullptr;
	}
	if (temp->district != fin->district)	//they cannot be reached if they are not connected
	{
		std::cout << "No safe path between cities" << std::endl;
		return nullptr;
	}

	Mountain* min = nullptr;
	int min_dist = MAX_INT;
	std::vector<Mountain*> solved;

	//set all distances to max, all previous to null
	for (std::vector<Mountain*>::iterator it = range.begin(); it != range.end(); it++)
		(*it)->distance = MAX_INT, (*it)->previous = nullptr;

	//set unique start properties
	temp->previous = nullptr;
	temp->distance = 0;
	temp->have_visited = true;
	solved.push_back(temp);

	while (fin->have_visited == false)
	{
		min_dist = MAX_INT;	//to next city from previous min
		min = nullptr;

		for (std::vector<Mountain*>::iterator it = solved.begin(); it != solved.end(); it++)	//each Mountain in solved
		{
			for (std::vector<Edge*>::iterator jt = (*it)->edge.begin(); jt != (*it)->edge.end(); jt++)	//each edge of that Mountain (from solved)
			{
				if ((*jt)->v->have_visited == false)	//never visited, setup
				{
					(*jt)->v->distance = (*it)->distance + (*jt)->weight;
					if ((*jt)->v->distance < min_dist)
					{
						min_dist = (*jt)->v->distance;
						min = (*jt)->v;
						temp = *it;
					}
				}
			}
		}
		min->have_visited = true;
		solved.push_back(min);
		min->previous = temp;		//have to assign this after the best case/true min has been found.
	}
	reset_visited();
	return fin;
}

void Graph_Primary::reset_visited()
{
	for (std::vector<Mountain*>::iterator it = range.begin(); it != range.end(); it++)
		(*it)->have_visited = false;
}
