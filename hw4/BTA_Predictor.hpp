#ifndef BTA_Predictor_HPP
#define BTA_Predictor_HPP

#include "Predictor.hpp"


#define TABLE_SIZE 1024


class BTA_Predictor : public Predictor
{
    private:
    int table[TABLE_SIZE] = {};
    int bcol[TABLE_SIZE] = {};
    bool colided;


    public:
    /* Constructor */
    BTA_Predictor();

    bool get_result(int branch, int target, bool f);

    bool predict(int branch, int target);

    bool collided(int branch, int target);

    /* Destructor */
    ~BTA_Predictor() = default;
};

#endif