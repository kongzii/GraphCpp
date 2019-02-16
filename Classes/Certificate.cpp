//
// Created by peter on 14/01/19.
//

#include "Graph.h"

int strToInt(std::string s) {

    std::string n;
    int sum = 0;
    int value = 1;

    for (int i = s.size() - 1; i >= 0; --i) {
        n = s[i];

        if (n == "1") {
            sum += value;
        }

        value *= 2;
    }

    return sum;

}

std::string removeFirstAndLast(std::string &s) {
    return s.substr(1, s.size() - 2);
}

Nodes Graph::getLeaves() const {
    Nodes leaves;

    for (const auto &v : this->adjList) {
        bool isLeave = false;

        if (this->direction == Directed && v.second.empty()) {
            isLeave = true;
        }

        if (this->direction == UnDirected && v.second.size() == 1) {
            isLeave = true;
        }

        if (isLeave) {
            leaves.insert(v.first);
        }
    }

    return leaves;
}

void Graph::removeCycles() {
    if (this->cycles.empty()) {
        std::__throw_length_error("No cycles in graph.");
    }

    for (const auto &cycle : this->cycles) {

        Node prev;
        prev.dummy = true;

        for (const auto &node : cycle) {
            if (!prev.dummy) {
                this->adjList.at(prev).erase(node);
            }

            prev = node;
        }

        this->adjList.at(cycle.back()).erase(cycle.front());
    }
}

bool Graph::checkCertificate(std::string certificate) const {
    if (certificate.length() != 2 * this->nOfVertices) {
        std::string msg = "Certificate node length " + std::to_string(certificate.length())
                          + " != 2 * " +
                          std::to_string(this->nOfVertices);
        std::__throw_invalid_argument(msg.c_str());
    }

    const auto zero_count = std::count(certificate.begin(), certificate.end(), '0');
    const auto one_count = std::count(certificate.begin(), certificate.end(), '1');

    if (zero_count != one_count) {
        std::string msg = "Certificate zero count " + std::to_string(zero_count)
                          + " != " + std::to_string(one_count) + " one count";
        std::__throw_invalid_argument(msg.c_str());
    }

    return true;
}

std::string Graph::getCertificate() const {
    auto graph = this->copy();

    Codes codes;
    for (int i = 0; i < this->nOfVertices + 1; i++) {
        codes[Node(i)] = std::make_pair(strToInt("01"), "01");
    }

    Nodes leaves;
    std::string certificate;

    while (graph.adjList.size() > 1) {

        leaves = graph.getLeaves();

        for (auto &parentNode : graph.adjList) {
            bool parentHadLeaves = false;

            // Code for current parent node
            std::vector<Code> tempCode;

            // Algoritm -> remove first 0 and last 1 from leave´s parent node code
            std::string tempBits = removeFirstAndLast( codes[parentNode.first].second );

            if (!tempBits.empty()) {
                // If there are bites after trimming, add them to code
                tempCode.emplace_back(strToInt(tempBits), tempBits);
                tempBits = "";
            }

            for (auto childNode = parentNode.second.begin(); childNode != parentNode.second.end(); ) {
                if (leaves.find(*childNode) != leaves.end()) {

                    // Emplace to parent´s node code
                    tempCode.emplace_back(codes[*childNode].first, codes[*childNode].second);

                    // Erase leave and move to next
                    graph.adjList.erase(*childNode);
                    childNode = parentNode.second.erase(childNode);

                    parentHadLeaves = true;

                } else {

                    // Not a leave, move to next
                    ++childNode;

                }
            }

            if (parentHadLeaves) {
                // If current node was parent of leaves

                // Sort leave´s codes in descending order
                // (algoritm says to prepend in ascending order, but we will be iterating from first to last)
                sort(tempCode.begin(), tempCode.end(), std::greater<Code>());

                // Create new code from them
                for (const auto &c : tempCode) {
                    tempBits += c.second;
                }

                tempBits = "0" + tempBits + "1";

                codes[parentNode.first] = make_pair(strToInt(tempBits), tempBits);

                if (graph.adjList.size() == 1) {
                    certificate = tempBits;
                    break;
                }
            }
        }
    }

    this->checkCertificate(certificate);

    return certificate;
}

void Graph::createFromCertificate(std::string certificate, int verticesCountFrom) {
    int t = verticesCountFrom - 1;
    int f = t;

    std::unordered_map<int, int> parents;

    for (const auto &c : certificate) {
        if (c == '0') {
            ++t;

            if (f >= verticesCountFrom) {
                parents[t] = f;
                this->addEdge(Node(f), Node(t));
            }

            f = t;
        } else if (c == '1') {
            f = parents[f];
        }
    }

    if (f != verticesCountFrom - 1) {
        // From vertex should end up where it started
        std::__throw_invalid_argument("Something went wrong in creation from certificate");
    }
}
