#ifndef SAT_Predictor_HPP
#define SAT_Predictor_HPP

#include "Predictor.hpp"

#define TABLE_SIZE 1024

class SAT_Predictor : public Predictor
{
  private:
    int table[TABLE_SIZE] = {};
    unsigned long long col[TABLE_SIZE] = {}; //keep track of the collision, store the upper bits
    bool colided;

  public:
    /* Constructor */
    SAT_Predictor();

    bool get_result(unsigned long long branch, unsigned long long target, bool f);

    bool predict(unsigned long long branch, unsigned long long target);

    bool collided(unsigned long long branch);
    /* Destructor */
    ~SAT_Predictor() = default;
};

#endif