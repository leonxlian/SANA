#include "EdgeMin.hpp"
#include "../utils/utils.hpp"
#include <vector>
#include <array>

double EdgeMin::denominator;

EdgeMin::EdgeMin(const Graph* G1, const Graph* G2): Measure(G1, G2, "emin") {EdgeMin::denominator=computeDenom(G1,G2);}

EdgeMin::~EdgeMin() {}

double EdgeMin::computeDenom(const Graph* G1, const Graph* G2) {
    return min(G1->getTotalEdgeWeight(), G2->getTotalEdgeWeight());
}

double EdgeMin::eval(const Alignment& A) {
#ifndef WEIGHT
    return kErrorScore;
#else
    return getEdgeMinSum(G1, G2, A);
#endif
}

static int _smallerEdge, _minEdgeSum;

double EdgeMin::getAligEdgeScore(const Graph* G1, const uint u1, const uint v1, const Graph* G2, const uint u2, const uint v2){
    // The maximum possible score is attained during a correct self-alignment, in which case every edge has a ratio of 1.
    int smaller = min(G1->getEdgeWeight(u1, v1), G2->getEdgeWeight(u2, v2));
    _smallerEdge = smaller;
    return smaller / EdgeMin::denominator;
}

#define MALE_FLY_EDGES (4158055+1000) // 1000 is extra space just to be sure
#define MAX_A_ARRAY (8*MALE_FLY_EDGES)
static double a[MAX_A_ARRAY];


// Score the contribution of peg's aligned edges while in hole1, optiotnally avoiding "avoidPeg" if it's a neighbor.
// Thanks to Marcus Longo for this idea (2025-01-27)
double EdgeMin::scoreOnePeg(const Graph* G1, const uint peg, const uint avoidPeg, const Graph* G2, const uint hole,
    const Alignment& A) {
    int ai=0, aSize=(G1->getAdjList(peg))->size() + (G1->getInjList(peg))->size() + 3; // 3 subtractions below
    assert(aSize <= MAX_A_ARRAY);

    // Process edges emanating from peg
    for(uint nbr : *(G1->getAdjList(peg))) if(nbr!=avoidPeg) // FIXME: can we avoid the branch by subtracting below the loop?
	a[ai++] = getAligEdgeScore(G1,peg,nbr, G2,hole,A[nbr]);
    assert(ai<=aSize);

    // Process edges targeting peg EXCEPT for any self-loop, which was already counted above.
    for(uint nbr : *(G1->getInjList(peg)))
	if(nbr!=avoidPeg && nbr!=peg) // FIXME: can we avoid the branch by subtracting below the loop?
	    a[ai++] = getAligEdgeScore(G1,nbr,peg, G2,A[nbr],hole);
    assert(ai<=aSize);
    return AccurateSum(ai, a);
}

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
