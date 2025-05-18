#ifndef EDGERATIO_HPP
#define EDGERATIO_HPP
#include "Measure.hpp"

class EdgeRatio: public Measure {
public:
    EdgeRatio(const Graph* G1, const Graph* G2);
    virtual ~EdgeRatio();
    double eval(const Alignment& A);
    static double getAligEdgeScore(const uint u1, const uint v1, const uint u2, const uint v2);
    static double getEdgeRatioSum(const Alignment &A);
    static double getIncChangeOp(uint peg, uint oldHole, uint newHole, const Alignment &A);
    static double getIncSwapOp(uint peg1, uint peg2, uint hole1, uint hole2, const Alignment &A);
private:
    static const Graph *G1, *G2;
    const int kErrorScore = -2;
    static double denominator;
    static double getRatio(double w1, double w2);
    static double computeIncChangeOp(uint peg, uint oldHole, uint newHole, const Alignment &A);
    static double computeIncSwapOp(uint peg1, uint peg2, uint hole1, uint hole2, const Alignment &A);
    double computeDenom();
};

#endif
