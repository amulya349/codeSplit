#ifndef PI_CALCULATOR_H
#define PI_CALCULATOR_H

#include "RandGen.h"

class PiCalculator {

public:
    PiCalculator(RandGen *randGen, int nPoints);

    virtual double calc();

private:

    RandGen *randGen;
    int nPoints;
};

#endif // PI_CALCULATOR_H

