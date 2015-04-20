#ifndef GRAPH_H
#define GRAPH_H

class Graph_Secondary;

class Graph_Primary
{
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

class Graph_Secondary /*: public Graph_Primary*/ {
public:
	Graph_Secondary();
	~Graph_Secondary();
	void addEdge();
protected:

private:
	std::vector<Edge*> edge;
	std::vector<Mountain*> mountain;		//secondary vertices
};

#endif //GRAPH_H