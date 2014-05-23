#ifndef RANDGENPARKMILLER_H
#define RANDGENPARKMILLER_H

#include "RandGen.h"
#include <cstdlib>

/**
 * @brief implements the RandGen-Interface via the Park And Miller algorithm
 */
class RandGenParkMiller : public RandGen {

public:

    RandGenParkMiller() : idum(12341234) {

    }

    virtual void init(unsigned long seed) {
        idum = seed;
    }


    virtual double nextDouble() {
        // don't know how this works but found it in a book:
        long k = 0;
        double result = 0;

        idum ^= MASK;
        k = idum / IQ;
        idum = IA * (idum - k*IQ)-IR*k;
        if(idum < 0) idum += IM;
        result = AM * idum;
        idum ^= MASK;
        return result;
    }

private:

    static const long IA = 16807L;
    static const long IM = 2147483647L;
    static const double AM = 1.0/IM;
    static const long IQ = 127773;
    static const long IR = 2836;
    static const long MASK = 123459876;

    long idum;


};


#endif // RANDGENPARKMILLER_H
