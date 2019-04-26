#include "COL_Predictor.hpp"

#include <iostream>

COL_Predictor::COL_Predictor()
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "COL";
    this->colided = false;
}

bool COL_Predictor::get_result(unsigned long long branch, unsigned long long target, bool f)
{
    bool v = (f == this->predict(branch, target));
    //update num of corre·ct and inccorect
    //the collision is out of consideration for COL
    if (v)
    {
        this->inc_cor();
    }
    else
    {
        int hashcode = (branch & 0x3ff);
        if (f)
        {
            //update the address to 1
            table[hashcode] = 1;
        }
        else
        {
            table[hashcode] = 0;
        }
        this->inc_inc();
    }
    return v;
}

bool COL_Predictor::predict(unsigned long long branch, unsigned long long target)
{
    int hashcode = (branch & 0x3ff);
    //check if the position is visted
    if (this->collided(branch))
    {
        //resort to STA way:
        if (branch > target)
        {
            table[hashcode] = 1;
            return true; 
        }
        else
        {
            table[hashcode] = 0;
            return false;
        }
    }
    int out = table[hashcode];
    if (out == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool COL_Predictor::collided(unsigned long long branch) 
{
    int hashcode = (branch & 0x3ff);

    if (this->col[hashcode] != branch)
    {
        //have a collision now
        this->col[hashcode] = branch;
        return true;
    }
    return false;
}