#include "PiCalculator.h"

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
