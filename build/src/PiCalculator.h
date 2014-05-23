#ifndef PI_CALCULATOR_H
#define PI_CALCULATOR_H

#include "RandGen.h"

class PiCalculator {

public:
    PiCalculator(RandGen *randGen, int nPoints) : randGen(randGen), nPoints(nPoints) {

    }

    virtual double calc() {
        int count = 0;
        for(int i = 0; i < nPoints; ++i) {
            double x = randGen->nextDouble();
            double y = randGen->nextDouble();

            if(x * x + y * y < 1.0) {
                ++count;
            }
        }

        return (double)count / (double)nPoints * 4.0;
    }

private:

    RandGen *randGen;
    int nPoints;
};

#endif // PI_CALCULATOR_H
