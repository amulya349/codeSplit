#ifndef RAND_GEN_H
#define RAND_GEN_H

/**
 * @brief interface (e.g. total abstract) class for random number generators
 */
class RandGen {

public:

    /**
     * @brief override this method to initialise the random number generator with seed
     */
    virtual void init(unsigned long int seed) = 0;

    /**
     * @brief override this method to get the next pseudo random number between [0.0 ... 1.0[
     */
    virtual double nextDouble() = 0;
};

#endif // RAND_GEN_H

