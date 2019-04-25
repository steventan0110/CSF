#include "BAH_Predictor.hpp"

#include <iostream>
BAH_Predictor::BAH_Predictor()
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "BAH";
    this->colided = false;
}

bool BAH_Predictor::get_result(int branch, int target, bool f)
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

bool BAH_Predictor::predict(int branch, int target)
{
    //suppress the unsued warning
    int i = target;
    i++;

    int hashcode = (branch & 0x3ff);
    //check if the position is visted
    if (this->collided(branch))
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

bool BAH_Predictor::collided(int branch) 
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

