#include "EdgeDifference.hpp"
#include <vector>

EdgeDifference::EdgeDifference(const Graph* G1, const Graph* G2): 
    Measure(G1, G2, "ed") {}

EdgeDifference::~EdgeDifference() {
}

double EdgeDifference::eval(const Alignment& A) {
    double edgeDifferenceSum = EdgeDifference::getEdgeDifferenceSum(G1, G2, A);
    return EdgeDifference::adjustSumToTargetScore(G1, G2, edgeDifferenceSum);
}

double EdgeDifference::getEdgeDifferenceSum(const Graph* G1, const Graph* G2, const Alignment &A) {
    double edgeDifferenceSum = 0;
    double c = 0; //use descriptive name please
    for (const auto& edge : *(G1->getEdgeList())) {
       uint node1 = edge[0], node2 = edge[1];
       double y = abs(G1->getEdgeWeight(node1,node2) - G2->getEdgeWeight(A[node1],A[node2])) - c;
       double t = edgeDifferenceSum + y;
       c = (t - edgeDifferenceSum) - y;
       edgeDifferenceSum = t;
    }
    return edgeDifferenceSum;
}

double EdgeDifference::adjustSumToTargetScore(const Graph *G1, const Graph *G2, const double edgeDifferenceSum) {
    uint m1=  G1->getNumEdges(), m2=G2->getNumEdges();
    double mean = edgeDifferenceSum / min(m1,m2);
    return 1 - mean / 2;
}
