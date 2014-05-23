#ifndef RANDGENPARKMILLER_H
#define RANDGENPARKMILLER_H

#include "RandGen.h"
#include <cstdlib>

/**
 * @brief implements the RandGen-Interface via the Park And Miller algorithm
 */
class RandGenParkMiller : public RandGen {

public:

    RandGenParkMiller();

    virtual void init(unsigned long seed);


    virtual double nextDouble();

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

