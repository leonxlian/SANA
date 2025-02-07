#ifndef EDGERATIO_HPP
#define EDGERATIO_HPP
#include "Measure.hpp"

class EdgeRatio: public Measure {
public:
    EdgeRatio(const Graph* G1, const Graph* G2);
    virtual ~EdgeRatio();
    double eval(const Alignment& A);
    static double getAligEdgeScore(const Graph* G1, const uint u1, const uint v1, const Graph* G2, const uint u2, const uint v2);
    static double getEdgeRatioSum(const Graph *G1, const Graph *G2, const Alignment &A);
private:
    const int kErrorScore = -2;
    static double getRatio(double w1, double w2);
};

#endif
