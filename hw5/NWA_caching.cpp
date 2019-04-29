#include <string>
#include <iostream>
#include "NWA_caching.hpp"

NWA_caching::NWA_caching()
{
    this->name = "NWA";
}

int NWA_caching::find_unused(int hashcode)
{
    unsigned long long min = block[hashcode][0];
    int pos = 0;
    if (min == 0)
    {
        return 0;
    }
    for (int i = 1; i < 4; i++)
    {
        if (block[hashcode][i] < min)
        {
            min = block[hashcode][i];
            pos = i;
        }
        if (min == 0)
        {
            return pos;
        }
    }
    return pos;
}

bool NWA_caching::check_hit(unsigned long long adr)
{
    int hash_set = ((adr & 0x7f8) >> 3);
    int hash_block = adr & 0x7;
    int adr_used = adr - hash_block;
    int pos = this->has_adr(adr);
    if (pos != -1)
    {
        //the adress in the cache, hit
        (this->hits)++;
        block[hash_set][pos] = cycle;
        return true;
    }
    else
    {
        //miss, need to store the value in a new place
        (this->miss)++;
        //check frequency of each slot
        int unused = this->find_unused(hash_set);
        block[hash_set][unused] = cycle;
        if (this->load)
        {
            //only update the memory if it's a load
            collision[hash_set][unused] = adr_used;
        }
        return false;
    }
}

int NWA_caching::has_adr(unsigned long long adr)
{
    (this->cycle)++;
    int hash_set = ((adr & 0x7f8) >> 3);
    int hash_block = adr & 0x7;
    unsigned long long adr_used = adr - hash_block; //remove the last three bits

    for (int i = 0; i < 4; i++)
    {
        if (collision[hash_set][i] == adr_used)
        {
            return i;
        }
    }
    return -1;
}

void NWA_caching::set_load(bool store)
{
    if (store)
    {
        this->load = false;
    }
    else
    {
        this->load = true;
    }
}