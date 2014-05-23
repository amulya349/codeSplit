#include "RandGenParkMiller.h"

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
