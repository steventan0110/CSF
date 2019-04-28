#include <string>
#include <iostream>
#include "ASS_caching.hpp"

ASS_caching::ASS_caching()
{
    this->name = "ASS";
}

int ASS_caching::find_unused()
{
    int min = check[0];
    int pos = 0;
    for (int i = 1; i < MAX; i++)
    {
        if (check[i] < min)
        {
            min = check[i];
            pos = i;
        }
    }
    return pos;
}


bool ASS_caching::check_hit(unsigned long long adr)
{
    int pos = this->has_adr(adr);
    if (pos != -1)
    {
        //the adress in the cache, hit
        (this->hits)++;
        //update the use of the slot
        check[pos] = cycle;
    }
    else
    {
        //miss, need to store the value in a new place
        (this->miss)++;
        //check frequency of each slot
        int unused = this->find_unused();
        check[unused] = cycle;
        collision[unused] = adr;
    }
}

int ASS_caching::has_adr(unsigned long long adr)
{
    (this->cycle)++;
    for (int i = 0; i < MAX; i++)
    {
        if (collision[i] == adr)
        {
            return i;
        }
    }
    return -1;
}

