#include "TAH_Predictor.hpp"

#include <iostream>

TAH_Predictor::TAH_Predictor()
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "TAH";
    this->colided = false;
}

bool TAH_Predictor::get_result(unsigned long long branch, unsigned long long target, bool f)
{
    bool v = (f == this->predict(branch, target));
    //update num of corre·ct and inccorect
    //the collision is out of consideration for BAH
   
    if (v)
    {
        //predict right, no update on the table
        if (this->colided)
        {
            //do not update the since we already update collision
            this->colided = false;
            return v;
        }
        this->inc_cor();
    }
    else
    {
        int hashcode = (target & 0x3ff);
        if (f)
        {
            //update the address to 1
            table[hashcode] = 1;
        }
        else
        {
            table[hashcode] = 0;
        }
        //after updating the value, check if it's colided
        //if colided, do not update the incorrect numebr
        if (this->colided) 
        {
            this->colided = false;
            return v;
        }
        this->inc_inc();
    }
    return v;
}

bool TAH_Predictor::predict(unsigned long long branch, unsigned long long target)
{
    int hashcode = (target & 0x3ff);
    //check if the position is visted
    if (this->collided(branch, target))
    {
        this->inc_coli();
        this->colided = true;
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

bool TAH_Predictor::collided(unsigned long long branch, unsigned long long target) 
{
    int hashcode = (target & 0x3ff);
    if (this->bcol[hashcode] != branch)
    {
        //have a collision now
        this->bcol[hashcode] = branch;
        return true;
    }
    
    return false;
}