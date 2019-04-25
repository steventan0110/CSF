#ifndef BAH_Predictor_HPP
#define BAH_Predictor_HPP

#include "Predictor.hpp"


#define TABLE_SIZE 1024


class BAH_Predictor : public Predictor
{
    private:
    int table[TABLE_SIZE] = {};
    int col[TABLE_SIZE] = {}; //keep track of the collision, store the upper bits
    bool colided;


    public:
    /* Constructor */
    BAH_Predictor();

    bool get_result(int branch, int target, bool f);

    bool predict(int branch, int target);

    bool collided(int branch); 

    /* Destructor */
    ~BAH_Predictor() = default;
};

#endif