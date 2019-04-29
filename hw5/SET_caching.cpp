#include <string>
#include <iostream>
#include "SET_caching.hpp"



SET_caching::SET_caching()
{
    this->name = "SET";
}

int SET_caching::find_unused(int hashcode)
{
    unsigned long long min = set[hashcode][0];
    int pos = 0;
    if (min == 0)
    {
        return 0;
    }
    for (int i = 1; i < 4; i++)
    {
        if (set[hashcode][i] < min)
        {
            min = set[hashcode][i];
            pos = i;
        }
        if (min == 0)
        {
            return pos; 
        }
    }
    return pos;
}


bool SET_caching::check_hit(unsigned long long adr)
{
    int pos = this->has_adr(adr);
    int hashcode = adr & 0x7ff;
    if (pos != -1)
    {
        //the adress in the cache, hit
        (this->hits)++;
        //update the use of the slot
        set[hashcode][pos] = cycle;
        return true;
    }
    else
    {
        //miss, need to store the value in a new place
        (this->miss)++;
        //check frequency of each slot
        int unused = this->find_unused(hashcode);
        set[hashcode][unused] = cycle;
        collision[hashcode][unused] = adr;
        return false;
    }
}

int SET_caching::has_adr(unsigned long long adr)
{
    (this->cycle)++;
    int hashcode = adr & 0x7ff;
    for (int i =0; i <4; i++)
    {
        if (collision[hashcode][i] == adr)
        {
            return i;
        }
    }
    return -1;
}

