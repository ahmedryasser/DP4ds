// File: Graph/Graph.hpp

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream> // ostream.
#include "ArrayT.hpp"
#include "ListL.hpp"
using namespace std;

enum ColorType {WHITE, GRAY, BLACK};
typedef struct {
    ColorType color;
    int discovered;
    int finished;
    int distance;
    int predecessor;
} graphVertex;

class Graph {
private:
    int _numVertices;
    bool _isDigraph;
    int _time;
    ArrayT<graphVertex> _vertex;            // The array of graph vertices.
    ArrayT<ListL<int> > _graph;             // The array of adjacency lists.
    ArrayT<ListLIterator<int> > _graphIter; // The array of list iterators.

public:
    Graph(bool isDigraph, int numVert);
    // Pre: 0 < numVert.
    // Post: The graph is allocated and initialized to have
    // zero edges and numVert vertices.

    ~Graph();
    // Post: The graph is deallocated.

    void breadthFirstSearch(int s, ostream &os);
    // Post: A breadth-first search of this graph beginning
    // at vertex s is output to os.
    // Post: Discovered time, finished time, distance from s,
    // and predecessor vertex for each vertex is output to os.

    void depthFirstSearch(int u, ostream &os);
    // Post: A depth-first search of this graph beginning
    // at vertex s is output to os.
    // Post: Discovered time, finished time, and predecessor vertex
    // for each vertex is output to os.

    void insertEdge(int from, int to);
    // Pre: 0 <= from < _numVertices, and 0 <= to < numVertices().
    // Post: If the edge <from, to> is not already in the graph,
    // it is installed; otherwise, the graph is unchanged.

    int numEdges();
    // Post: The number of edges is returned.

    void removeEdge(int from, int to);
    // Pre: 0 <= from < _numVertices, and 0 <= to < _numVertices.
    // Post: If the edge <from, to> is in the graph, it is removed;
    // otherwise, the graph is unchanged.

    void writeAdjacencyLists(ostream &os);
    // Post: The adjacency lists for each vertex with a nonempty list
    // is output to os.

    void writeComponents(ostream &os);
    // Post: A list of all the connected components is output to os,
    // with a count of how many components exist.

    void writePath(int from, int to, ostream &os);
    // Pre: 0 <= from < _numVertices, and 0 <= to < _numVertices.
    // Post: If there is a path from vertex "from" to vertex "to" a
    // path of smallest distance and its length is output to os;
    // otherwise, a statement that no path exists is output.

private:
    void bfs(int s, ostream &os);
    // Post: A breadth-first search of this graph beginning at
    // vertex s is performed without initialization.

    void dfs(int u, ostream &os);
    // Pre: color for each vertex is well-defined and the color
    // of vertex u is WHITE.
    // Post: A depth-first search of this graph beginning at
    // vertex u is performed with the color of each vertex visited,
    // including the color of u, set to BLACK.
    // Post: Vertex u is output to os.

    void initGraph();
    // Post: Every vertex of the graph is initialized in preparation
    // for a breadth-first or depth-first search.

    void writePathHelper(int from, int to, ostream &os);

    void writeVerticesPostBreadth(ostream &os);
    // Post: Discovered time, finished time, predecessor vertex,
    // and distance from s,for each vertex is output to os.

    void writeVerticesPostDepth(ostream &os);
    // Post: Discovered time, finished time, and predecessor
    // vertex for each vertex is output to os.
};

#endif
