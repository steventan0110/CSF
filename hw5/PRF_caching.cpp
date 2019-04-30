#include <string>
#include <iostream>
#include "PRF_caching.hpp"

PRF_caching::PRF_caching()
{
    this->name = "PRF";
}

int PRF_caching::find_unused(int hashcode)
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

bool PRF_caching::check_hit(unsigned long long adr)
{
    int hash_set = ((adr & 0x7f8) >> 3);
    int hash_block = adr & 0x7;
    unsigned long long adr_used = adr - hash_block;
    int pos = this->has_adr(adr);
    if (pos != -1)
    {
        //the adress in the cache, hit
        //catch hits not influenced
        (this->hits)++;
        block[hash_set][pos] = cycle;
        return true;
    }
    else
    {
        //miss, need to store the value in a new place
        (this->miss)++;

        if (this->load)
        {
            //check frequency of each slot
            int unused = this->find_unused(hash_set);
            block[hash_set][unused] = cycle;
            (this->cycle)++;
            
            int new_set = (hash_set + 1) & 0xff;
            //only update the memory if it's a load
            collision[hash_set][unused] = adr_used;
            int unused1 = this->find_unused(new_set);
            collision[new_set][unused1] = adr_used + 8;
            block[new_set][unused1] = cycle;
        }
        return false;
    }
}

int PRF_caching::has_adr(unsigned long long adr)
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

void PRF_caching::set_load(bool store)
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