#ifndef BTA_Predictor_HPP
#define BTA_Predictor_HPP

#include "Predictor.hpp"


#define TABLE_SIZE 1024


class BTA_Predictor : public Predictor
{
    private:
    int table[TABLE_SIZE] = {};
    unsigned long long bcol[TABLE_SIZE] = {};
    bool colided;


    public:
    /* Constructor */
    BTA_Predictor();

    bool get_result(unsigned long long branch, unsigned long long target, bool f);

    bool predict(unsigned long long branch, unsigned long long target);

    bool collided(unsigned long long branch, unsigned long long target);

    /* Destructor */
    ~BTA_Predictor() = default;
};

#endif