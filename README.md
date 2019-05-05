# GraphCpp
C++ implementation of Graph. Along with algorithms for Spanning Tree, Strongly Connected Components, distance/path between two points and others.

Supports both directed and undirected graphs.

## Implemented algorithms

- Create Spanning Tree from original graph
- Find Strongly Connected Components and create graph from them
- Calc ST certificate / Create graph from provided certificate
- Find and create vector of separated graphs from main one
- Longest path
- Euler theorem
- Find and remove cycles
- Adjacent matrix representation 
- Distance between A and B
- Shortest path between A and B
- Find leaves

## About

Created little by little during my study of Artificial Intelligence at Prague.

## Sample usage

```C++
int main(int argc, char **argv) {
    int N, E;
    
    std::cin >> N >> E; 

    // Create directed graph with N vertices
    Graph graph(Directed, N);

    int V1, V2;
    for (int i = 0; i < E; ++i) {
        std::cin >> V1 >> V2;
        
        // Adding edge by edge from standart input
        graph.addEdge( Node(V1), Node(V2) );
    }

    // Executing some algorithm
    std::string certificate = graph.getCertificate();
    
    std::cout << certificate << std::endl;

}
```