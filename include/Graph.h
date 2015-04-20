#ifndef GRAPH_H
#define GRAPH_H

class Graph_Secondary;

//writing traversal algorithms is going to be a f**king nightmare.
//but that's fine.
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

#endif //GRAPH_H
