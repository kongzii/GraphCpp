#include <bits/stdc++.h>

#include "Classes/print.h"
#include "Classes/Graph.h"
#include "Classes/Rosetta/comb.h"
#include "Classes/DisjointSet.h"

#define DEBUG true

#if DEBUG

#include <libgen.h>
#include <unistd.h>
#include <limits.h>

    std::string getpath() {
        char buf[PATH_MAX + 1];
        if (readlink("/proc/self/exe", buf, sizeof(buf) - 1) == -1)
            throw std::string("readlink() failed");
        std::string str(buf);
        return str.substr(0, str.rfind('/'));
    }

#endif

int main(int argc, char **argv) {
#if DEBUG
    clock_t tStart = clock();
    std::string pubPath = getpath() + "/../datapub/" + std::string(argv[1]);

    std::ifstream taskInput(pubPath + ".in");
    #define cin taskInput
#endif

    int N, E;

#if DEBUG
    cin >> N >> E;
#else
    scanf("%d %d", &N);
#endif

    Graph graph(Directed, N);

    int V1, V2;
    for (int i = 0; i < E; ++i) {
#if DEBUG
        cin >> V1 >> V2;
        // std::cout << V1 << " " << V2 << std::endl;
#else
        scanf("%d %d", &V1, &V2);
#endif

        graph.addEdge( Node(V1), Node(V2) );
    }

    std::string myOutput = "myOutput";

#if DEBUG
    std::ifstream taskOutput(pubPath + ".out");
    std::string rightOutput;
    std::getline(taskOutput, rightOutput);

    printf("\n\n");
    printf("My output:\t\t%s \n", myOutput.c_str());
    printf("Right output:\t%s \n", rightOutput.c_str());
    printf("PASSED:\t\t\t%s \n", (!myOutput.compare(rightOutput) ? "YES" : "NO"));

    printf("Time taken:\t\t%.2fs \n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
#else
    printf("%s\n", myOutput.c_str());
#endif

}

// Ended on asg3