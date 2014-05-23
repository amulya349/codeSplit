#ifndef RAND_GEN_ANSI_H
#define RAND_GEN_ANSI_H

#include "RandGen.h"
#include <cstdlib>

/**
 * @brief implements the RandGen-Interface by calling the ansi-functions
 */
class RandGenAnsi : public RandGen {

public:

    virtual void init(unsigned long seed) {
        srand((unsigned int)seed);
    }

    virtual double nextDouble() {
        return ((double)rand())/((double)RAND_MAX + 1.0);
    }
};

#endif // RAND_GEN_ANSI_H
