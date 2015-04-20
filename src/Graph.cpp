//NOTE: THIS IS GOING TO BE BROKEN FOR A VERY LONG TIME
//This is essentially a copy-paste from assignemnt 8 with almost no variation until I rewrite all of the functions

#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include"Graph.h"
#include"Mountain.h"


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
