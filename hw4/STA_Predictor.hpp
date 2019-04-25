#ifndef STA_Predictor_HPP
#define STA_Predictor_HPP

#include "Predictor.hpp"


class STA_Predictor : public Predictor
{
  public:
    /* Constructor */
    STA_Predictor();

    bool get_result(int branch, int target, bool f);

    bool predict(int branch, int target);

    /* Destructor */
    ~STA_Predictor() = default;
};

#endif