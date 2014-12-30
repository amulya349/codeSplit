#include "RandGenAnsi.h"

    virtual double nextDouble() {
        return ((double)rand())/((double)RAND_MAX + 1.0);
    }
