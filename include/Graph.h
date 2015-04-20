#ifndef GRAPH_H
#define GRAPH_H

struct Vertex;

struct Edge
{
	//construct/destruct
	Edge();
	Edge(Vertex*, int&);
	~Edge();

	Vertex* v;
	int weight;
};

class Vertex : public Mountain {
public:
	//construct/destruct
	Vertex();
	Vertex(std::string&);	//make with name
	~Vertex();

	bool have_visited;
	int district;
	int distance;

private:
	Vertex* previous;

	std::string name;
	std::vector<Edge*> edge;
};

class Graph
{
public:
	//construct/destruct
	Graph();
	~Graph();

	//by name
	void add_edge(int&, int&, int);	//v1, v2, weight
	void add_vertex(std::string&);	//name
	void print_vertices();
	void display_edges(Vertex*);
	void BFTraversal();
	void BFTraversal(std::string&);
	Vertex* shortest_path(std::string&, std::string&);		//
	Vertex* shortest_distance(std::string&, std::string&);	//return destination-Vertex?  || dijkastra's
	void assign_districts();

private:
	std::vector<Vertex*> vertices;
	Vertex* district_log[5][10];

	void reset_visited();	//private because why not
};

#endif //GRAPH_H