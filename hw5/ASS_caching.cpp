#include <string> 
#include <iostream>
#include "ASS_caching.hpp"

ASS_caching::ASS_caching()
{
    this->name = "ASS";
}

bool ASS_caching::check_hit(unsigned long long adr)
{
    
    if (adr > MAX)
    {
        //run out of space
    }
    if (check[hashcode] != adr) 
    {
        //std::cout<< "reach here" << std::endl;
        //miss the cache address, do update on the table
        check[hashcode] = adr;
        //increment number of miss:
        (this->miss)++;
        return false; 
    }
    (this->hits)++; 
    return true;
}