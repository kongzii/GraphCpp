//
// Created by peter on 20/01/19.
//

#include "Graph.h"

Graph Graph::createFromSCC() const {
    Graph sccGraph(this->direction, this->nOfComponents);

    std::unordered_map<int, std::unordered_set<int>> calculated;

    int myComp, neighborComp;
    Node myCompNode, neighborCompNode;
    for (const auto &n : this->adjList) {
        myComp = nodeToComponent.at(n.first.n);
        myCompNode = Node(myComp);

        sccGraph.adjList[myCompNode];

        for (const auto &v : n.second) {
            neighborComp = nodeToComponent.at(v.n);
            neighborCompNode = Node(neighborComp);

            if (myComp != neighborComp && calculated[myComp].find(neighborComp) == calculated[myComp].end()) {
                sccGraph.addEdge(myCompNode, neighborCompNode);
                calculated[myComp].insert(neighborComp);
            }
        }
    }

    return sccGraph;
}

void Graph::findSCC() {
    if (this->direction == UnDirected) {
        std::__throw_invalid_argument("Graph must be Directed for SCC");
    }

    auto *disc = new int[this->nOfVertices + 1];
    auto *low = new int[this->nOfVertices + 1];
    auto *stackMember = new bool[this->nOfVertices + 1];
    auto *st = new std::stack<int>();

    for (int i = 0; i < this->nOfVertices; ++i) {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    for (int i = 0; i < this->nOfVertices; ++i) {
        if (disc[i] == NIL) {
            sccUtil(i, disc, low, st, stackMember);
        }
    }

    for (auto &node : this->adjList) {
        node.first.component = this->nodeToComponent.at(node.first);
        for (auto &connected : node.second) {
            connected.component = this->nodeToComponent.at(connected);
        }
    }
}

void Graph::sccUtil(int u, int disc[], int low[], std::stack<int> *st, bool stackMember[]) {
    static int time = 0;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

    // Go through all vertices adjacent to this
    if (this->adjList.count(Node(u))) {
        for (const auto &n : this->adjList.at(Node(u))) {
            int v = n.n;  // v is current adjacent of 'u'

            // If v is not visited yet, then recur for it
            if (disc[v] == NIL) {
                sccUtil(v, disc, low, st, stackMember);

                // Check if the subtree rooted with 'v' has a
                // connection to one of the ancestors of 'u'
                // Case 1 (per above discussion on Disc and Low value)
                low[u] = std::min(low[u], low[v]);
            }

                // Update low value of 'u' only of 'v' is still in stack
                // (i.e. it's a back edge, not cross edge).
                // Case 2 (per above discussion on Disc and Low value)
            else if (stackMember[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
    }

    // Head node found, pop the stack and print an SCC
    if (low[u] == disc[u]) {
        int w;

        int component = NIL;
        Nodes nodes;

        while (st->top() != u) {
            w = (int) st->top();

            // Add some special test to specify number of component
            if (component == NIL) {
                component = this->nOfComponents;
            }

            nodes.insert(w);

            stackMember[w] = false;
            st->pop();
        }

        w = (int) st->top();

        // Add some special test to specify number of component
        if (component == NIL) {
            component = this->nOfComponents;
        }

        nodes.insert(w);
        this->components[component] = nodes;

        for (const auto &v : nodes) {
            // std::cout<<v.n<<" "<<component<<std::endl;
            this->nodeToComponent[v] = component;
        }

        this->nOfComponents += 1;

        stackMember[w] = false;
        st->pop();
    }
}