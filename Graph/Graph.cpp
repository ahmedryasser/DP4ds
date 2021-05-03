// File: Graph/Graph.cpp

#include <iostream>
#include "Graph.hpp"
#include "QueueL.hpp"
using namespace std;

// ========= Constructor =========
Graph::Graph(bool isDigraph, int numVert) :
    _numVertices(numVert),
    _isDigraph(isDigraph),
    _vertex(numVert),
    _graph(numVert),
    _graphIter(numVert) {
    for (int i = 0; i < numVert; i++) {
        _graphIter[i].setIterListL(&_graph[i]);
    }
    }

// ========= Destructor =========
Graph::~Graph() {
    for (int i = 0; i < _numVertices; i++) {
        _graph[i].clear();
    }
}

// ========= Breadth first search =========
void Graph::breadthFirstSearch(int s, ostream &os) {
    initGraph();
    os << endl;
    bfs(s, os);
    writeVerticesPostBreadth(os);
}

void Graph::bfs(int s, ostream &os) {
    _vertex[s].color = GRAY;
    _vertex[s].distance = 0;
    QueueL<int> queue;
    _vertex[s].predecessor = -1;
    _vertex[s].discovered = ++_time;
    queue.enqueue(s);
    while (!queue.isEmpty()){
        int u = queue.dequeue();
        os << u;
        _vertex[u].finished = ++_time;
        for (_graphIter[u].first(); !_graphIter[u].isDone(); _graphIter[u].next()){
            int v = _graphIter[u].currentItem();
            if (_vertex[v].color == WHITE){
                _vertex[v].color = GRAY;
                _vertex[v].distance = _vertex[u].distance +1;
                _vertex[v].predecessor = u;
                _vertex[v].discovered = ++_time;
                queue.enqueue(v);
            }

        }
        _vertex[u].color = BLACK;
    }

}

// ========= Depth first search =========
void Graph::depthFirstSearch(int s, ostream &os) {
    initGraph();
    os << endl;
    dfs(s, os);
    writeVerticesPostDepth(os);
}

void Graph::dfs(int u, ostream &os) {
    os << u;
    _vertex[u].discovered = ++_time;
    _vertex[u].color = GRAY;
    for (_graphIter[u].first(); !_graphIter[u].isDone(); _graphIter[u].next()){
        int v = _graphIter[u].currentItem();
        if (_vertex[v].color == WHITE){
            _vertex[v].predecessor = u;
            dfs(v, os);
        }

    }
    _vertex[u].color = BLACK;
    _vertex[u].finished = ++_time;

}

// ========= initGraph =========
void Graph::initGraph() {
    _time = 0;
    for (int i = 0; i < _numVertices; i++) {
        _vertex[i].color = WHITE;
        _vertex[i].discovered = -1;
        _vertex[i].finished = -1;
        _vertex[i].distance = -1;
        _vertex[i].predecessor = -1;
    }
}

// ========= insertEdge =========
void Graph::insertEdge(int from, int to) {
    if ((from < 0) || (_numVertices <= from) || (to < 0) || (_numVertices <= to)) {
        cerr << "insertEdge precondition violated: from or to out of range." << endl;
        cerr << "from == " << from << "  to == " << to << endl;
        throw -1;
    }
    if (!_graph[from].contains(to)) {
        _graph[from].prepend(to);
    }
    if (!_isDigraph && !_graph[to].contains(from)) {
        _graph[to].prepend(from);
    }
}

// ========= numEdges =========
int Graph::numEdges() {
    int result = 0;
    for (int i = 0; i< _numVertices; i++){
        result += _graph[i].length();
    }
    return _isDigraph ? result : result/2;
}

// ========= removeEdge =========
void Graph::removeEdge(int from, int to) {
    _graph[from].remove(to);
    if (!_isDigraph) {
        _graph[to].remove(from);
    }
}

// ========= writeAdjacencyLists =========
void Graph::writeAdjacencyLists(ostream &os) {
    os << "Adjacency lists" << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": ";
        os << _graph[i] << endl;
    }
}

// ========= writeComponents =========
void Graph::writeComponents(ostream &os) {
    int numComponents = 0;
    initGraph();
    for (int u = 0; u < _numVertices; u++) {
        if (_vertex[u].color == WHITE) {
            os << "Connected Component: " << endl;
            dfs(u, os);
            os << endl;
            numComponents++;
        }
    }
    os << numComponents;
}

// ========= writePath =========
void Graph::writePath(int from, int to, ostream &os) {
    if ((from < 0) || (_numVertices <= from) || (to < 0) || (_numVertices <= to)) {
        cerr << "minimumDistance precondition violated: from or to out of range." << endl;
        cerr << "from == " << from << "  to == " << to << endl;
        throw -1;
    }
    initGraph();
    os << "\nBreadth-first search from " << from << ": ";
    bfs(from, os);
    os << "\nPath from " << from << " to " << to << " is: ";
    writePathHelper(from, to, os);
    if (_vertex[to].distance != -1) {
        os << "\nDistance = " << _vertex[to].distance << endl;
    }
}

void Graph::writePathHelper(int from, int to, ostream &os) {
    if (to == from){
        os << to;
    }
    else if(_vertex[to].predecessor == -1){
        os << " No path exists";
    }
    else{
        writePathHelper(from, _vertex[to].predecessor, os);
        os<< to;
    }
}

// ========= write vertices =========
void Graph::writeVerticesPostBreadth(ostream &os) {
    os << "\n\nDiscovered/finished, predecessor, distance";
    os << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": "
           << _vertex[i].discovered << "/" << _vertex[i].finished << ", "
           << _vertex[i].predecessor << ", "
           << _vertex[i].distance << endl;
    }
}

void Graph::writeVerticesPostDepth(ostream & os) {
    os << "\n\nDiscovered/finished, predecessor";
    os << endl;
    for (int i = 0; i < _numVertices; i++) {
        os << i << ": "
           << _vertex[i].discovered << "/" << _vertex[i].finished << ", "
           << _vertex[i].predecessor << endl;
    }
}
