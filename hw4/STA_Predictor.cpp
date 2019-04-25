#include "STA_Predictor.hpp"

STA_Predictor::STA_Predictor() 
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "STA";
}


bool STA_Predictor::get_result(int branch, int target, bool f)
{
        bool v = (f == this->predict(branch, target));
        //update num of correct and inccorect
        //the collision is out of consideration for STA
        if (v) 
        {
            this->inc_cor();
        }
        else 
        {
            this->inc_inc();
        }
        return v;
}

bool STA_Predictor::predict(int branch, int target)
{
        if (branch > target) {
                return true;
        }
        return false;
}