#include "SAT_Predictor.hpp"

#include <iostream>
SAT_Predictor::SAT_Predictor()
{
    this->coli = 0;
    this->incor = 0;
    this->correct = 0;
    this->name = "SAT";
    this->colided = false;
}

bool SAT_Predictor::get_result(unsigned long long branch, unsigned long long target, bool f)
{
    bool v = (f == this->predict(branch, target));
    int hashcode = (branch & 0x3ff);
    //update num of correct and inccorect
    //the collision is out of consideration for SAT
    if (v)
    {
        if (f)
        {
            table[hashcode] += 1;
            if (table[hashcode] > 3)
            {
                table[hashcode] = 3;
            }
        }
        else
        {
            table[hashcode] -= 1;
            if (table[hashcode] < 0)
            {
                table[hashcode] = 0;
            }
        }

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
        if (f)
        {
            //update the address to 1
            table[hashcode] += 1;
            if (table[hashcode] > 3)
            {
                table[hashcode] = 3;
            }
        }
        else
        {
            table[hashcode] -= 1;
            if (table[hashcode] < 0)
            {
                table[hashcode] = 0;
            }
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

bool SAT_Predictor::predict(unsigned long long branch, unsigned long long target)
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
    if (out <= 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool SAT_Predictor::collided(unsigned long long branch) 
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
