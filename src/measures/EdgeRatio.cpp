#include "EdgeRatio.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <array>

EdgeRatio::EdgeRatio(const Graph* G1, const Graph* G2): Measure(G1, G2, "er") {}
EdgeRatio::~EdgeRatio() {}

double EdgeRatio::eval(const Alignment& A) {
#ifndef WEIGHT
    return kErrorScore;
#else
    return getEdgeRatioSum(G1, G2, A);
    // The maximum possible score is attained during a correct self-alignment, in which case every edge has a ratio of 1.
#endif
}

double EdgeRatio::getRatio(double w1, double w2) {
    if (w1 == 0 and w2 == 0) return 0;
    double r = (abs(w1) < abs(w2) ? w1/w2 : w2/w1);
    // At this point, r is in [-1,1], but we want it in [0,1], so add 1 and divide by 2
    r = (r+1)/2;
    assert(r >= 0 and r <= 1);
    return r;
}

double EdgeRatio::getAligEdgeScore(const Graph* G1, const uint u1, const uint v1, const Graph* G2, const uint u2, const uint v2){
    return getRatio(G1->getEdgeWeight(u1, v1), G2->getEdgeWeight(u2, v2)) / G1->getNumEdges();
}


double EdgeRatio::getEdgeRatioSum(const Graph *G1, const Graph *G2, const Alignment &A) {
#ifndef WEIGHT
    return 0;
#else
    vector<double> weights;
    weights.reserve(G1->getNumEdges());
    for (const auto& edge : *(G1->getEdgeList())) {
	uint node1 = edge[0], node2 = edge[1];
	weights.push_back(getAligEdgeScore(G1,node1,node2, G2,A[node1],A[node2]));
	// We don't need to include the reverse edge here in the directed graph case, because *if* a reverse edge of
	// (u,v) exists, it's actually *in* this edgeList.
    }
    return AccurateSum(weights);
#endif
}

