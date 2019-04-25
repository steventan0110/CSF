#ifndef TWO_Predictor_HPP
#define TWO_Predictor_HPP

#include "Predictor.hpp"


#define TABLE_SIZE 1024


class TWO_Predictor : public Predictor
{
    private:
    int his[TABLE_SIZE] = {}; //keep the history bits
    int table[32] = {}; //keep the taken or not taken information
    int col[TABLE_SIZE] = {}; //keep track of the collision, store the upper bits
    bool colided;


    public:
    /* Constructor */
    TWO_Predictor();

    bool get_result(int branch, int target, bool f);

    bool predict(int branch, int target);

    bool collided(int branch); 

    /* Destructor */
    ~TWO_Predictor() = default;
};

#endif