#include "DIR_caching.hpp"
#include <string> 
#include <iostream>


DIR_caching::DIR_caching()
{
    this->name = "DIR";
}

bool DIR_caching::check_hit(unsigned long long adr)
{
    
    int hashcode = adr & 0x1fff;
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