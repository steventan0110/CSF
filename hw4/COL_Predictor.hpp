#ifndef COL_Predictor_HPP
#define COL_Predictor_HPP

#include "Predictor.hpp"

#define TABLE_SIZE 1024

class COL_Predictor : public Predictor
{
  private:
    int table[TABLE_SIZE] = {};
    int col[TABLE_SIZE] = {}; //keep track of the collision, store the upper bits
    bool colided;

  public:
    /* Constructor */
    COL_Predictor();

    bool get_result(int branch, int target, bool f);

    bool predict(int branch, int target);

    bool collided(int branch);
    /* Destructor */
    ~COL_Predictor() = default;
};

#endif