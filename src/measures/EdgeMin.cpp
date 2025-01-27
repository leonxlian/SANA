#include "EdgeMin.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <array>

EdgeMin::EdgeMin(const Graph* G1, const Graph* G2): Measure(G1, G2, "emin") {}
EdgeMin::~EdgeMin() {}

double EdgeMin::eval(const Alignment& A) {
#ifndef WEIGHT
    return kErrorScore;
#else
    return getEdgeMinSum(G1, G2, A);
#endif
}

double EdgeMin::getAligEdgeScore(const Graph* G1, const uint u1, const uint v1, const Graph* G2, const uint u2, const uint v2){
    // The maximum possible score is attained during a correct self-alignment, in which case every edge has a ratio of 1.
    return min(G1->getEdgeWeight(u1, v1), G2->getEdgeWeight(u2, v2)) / min(G1->getTotalEdgeWeight(), G2->getTotalEdgeWeight());
}

#define MALE_FLY_EDGES 4158055
#define MAX_A_ARRAY (8*MALE_FLY_EDGES)
static double a[MAX_A_ARRAY];

double EdgeMin::getEdgeMinSum(const Graph *G1, const Graph *G2, const Alignment &A) {
#ifndef WEIGHT
    return 0;
#else
    int ai=0, aSize=G1->getNumEdges();
    assert(aSize <= MAX_A_ARRAY);
    for (const auto& edge : *(G1->getEdgeList())) {
	uint node1 = edge[0], node2 = edge[1];
	a[ai++] = getAligEdgeScore(G1,node1,node2, G2,A[node1],A[node2]);
	// We don't need to include the reverse edge here in the directed graph case, because *if* a reverse edge of
	// (u,v) exists, it's actually *in* this edgeList.
	assert(ai<=aSize);
    }
    return AccurateSum(ai, a);
#endif
}

