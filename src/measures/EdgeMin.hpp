#ifndef EDGEMIN_HPP
#define EDGEMIN_HPP
#include "Measure.hpp"

class EdgeMin: public Measure {
public:
    EdgeMin(const Graph* G1, const Graph* G2);
    virtual ~EdgeMin();
    double eval(const Alignment& A);
    static double scoreOnePeg(const Graph* G1, const uint peg1, const uint avoidPeg, const Graph* G2, const uint hole,
	const Alignment& A);
    static double getAligEdgeScore(const Graph* G1, const uint u1, const uint v1, const Graph* G2, const uint u2, const uint v2);
    static double getEdgeMinSum(const Graph *G1, const Graph *G2, const Alignment &A);
private:
    static double denominator;
    double computeDenom(const Graph* G1, const Graph* G2);
};

#endif //EDGEDIFFERENCE_HPP
