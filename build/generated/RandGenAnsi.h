#ifndef RAND_GEN_ANSI_H
#define RAND_GEN_ANSI_H

#include "RandGen.h"
#include <cstdlib>

/**
 * @brief implements the RandGen-Interface by calling the ansi-functions
 */
class RandGenAnsi : public RandGen {

public:

    virtual void init(unsigned long seed);

    virtual double nextDouble();
};

#endif // RAND_GEN_ANSI_H

