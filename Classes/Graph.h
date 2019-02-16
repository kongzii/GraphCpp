//
// Created by peter on 11/01/19.
//

#ifndef Z2018_GRAPH_H
#define Z2018_GRAPH_H

#include <bits/stdc++.h>
#include "Node.h"
#include "Edge.h"
#include "JoinTable.h"

#define INF 0x3f3f3f3f
#define NIL -1

typedef std::unordered_map<Node, Nodes> AdjacencyList;
typedef std::vector<Node> Path;
typedef std::priority_queue<Edge, EdgePath, std::greater<Edge> > EdgePriorityQueue;

typedef std::pair<int, std::string> Code;
typedef std::unordered_map<Node, Code> Codes;

enum GraphDirection {Directed, UnDirected};

void printNodes(const Nodes &nodes);

class Graph {
    typedef std::vector<Graph> Graphs;

public:
    GraphDirection direction;

    AdjacencyList adjList;
    Nodes nodes;
    Edges edges;

    int nOfVertices;

    Nodes cycleNodes;
    std::unordered_map<Node, int> nodeToCycle;
    std::vector<Path> cycles;

    std::unordered_map<Node, int> nodeToComponent;
    std::unordered_map<int, Nodes> components;
    int nOfComponents = 0;

    int size = 0;
    int totalCost = 0;

    // Creation

    Graph(GraphDirection, int);
    Graph(GraphDirection, std::string, int);

    void createFromCertificate(std::string, int);

    Graph copy() const;

    void addEdge(Edge);
    void addEdge(Node, Node);

    // Algorithms

    void findCycles();
    bool isCycleNode(Node n) { return this->cycleNodes.find(n) != this->cycleNodes.end(); }
    void removeCycles();

    Graph createSpanningTree(const Node fromNode);
    Graph createSpanningTree(const EdgePath path);
    Graph createSpanningTree(const EdgePaths paths);

    int getDistance(const Node, const Node) const;

    void findSCC();
    void sccUtil(int, int [], int [], std::stack<int> *, bool []);
    Graph createFromSCC() const;

    Path findPath(const Node, const Node);

    Nodes getLeaves() const;
    std::string getCertificate() const;
    bool checkCertificate(std::string) const;

    int countOddNodes() const;
    bool checkEulerTheorem() const;
    Path getEulerPath() const;

    Path getHamiltonian() const;

    Graphs getDisconnected() const;

    void findLongestPathsFrom(const Node &from) const;

    // Utils

    void print() const;
    void printCycles() const;
    void printMatrix() const;
};


#endif //Z2018_GRAPH_H
