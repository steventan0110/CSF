#ifndef STA_Predictor_HPP
#define STA_Predictor_HPP

#include "Predictor.hpp"


class STA_Predictor : public Predictor
{
  public:
    /* Constructor */
    STA_Predictor();

    bool get_result(unsigned long long branch, unsigned long long target, bool f);

    bool predict(unsigned long long branch, unsigned long long target);

    /* Destructor */
    ~STA_Predictor() = default;
};

#endif