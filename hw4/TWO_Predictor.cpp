#include "TWO_Predictor.hpp"

#include <iostream>
TWO_Predictor::TWO_Predictor()
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "TWO";
    this->colided = false;
}

bool TWO_Predictor::get_result(int branch, int target, bool f)
{
    bool v = (f == this->predict(branch, target));
    int hashcode = (branch & 0x3ff);
    int history = his[hashcode];
    //update num of corre·ct and inccorect
    //the collision is out of consideration for TWO
    if (v)
    {
        //predict right, no update on the table
        //but the history table shift and add 1 or 0
        if (f)
        {
            his[hashcode] = ((history << 1) & 0x1f) + 1;
        }
        else
        {
            his[hashcode] = ((history << 1) & 0x1f);
        }
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
        
        if (f)
        {
            his[hashcode] = ((history << 1) & 0x1f) + 1;
            //update the address to 1
            table[history] = 1;
        }
        else
        {
            his[hashcode] = ((history << 1) & 0x1f);
            table[history] = 0;
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

bool TWO_Predictor::predict(int branch, int target)
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
    int h = his[hashcode];
    //map the history into table
    int out = table[h];
    if (out == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TWO_Predictor::collided(int branch)
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